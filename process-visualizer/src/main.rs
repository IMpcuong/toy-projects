mod process_collector;

use std::{
  fs::File,
  io::{Read, Write},
  net::TcpListener,
  path::Path,
  process::Command,
  // NOTE: `Multi-producers, single-consumer FIFO queue communication primitives`.
  // sync::{mpsc::channel, Arc, Mutex},
  time::{Duration, Instant},
};

use crate::process_collector::*;

// NOTE: Define the interval between updates (in seconds).
const UPDATE_INTERVAL_SEC: u64 = 5;

fn main() -> std::io::Result<()> {
  // NOTE: Open process-statistics file for writing with an initial update.
  let mut proc_invoker = invoke_process_with(
    Command::new("ps"),
    vec!["-eo", "pid,pcpu,pmem,pri,comm"],
  )
  .unwrap();

  // NOTE: Over-complicated as described on the `process_collector.rs`.
  let output =
    convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())?;
  redirect_procs_stat_to_file(output, Path::new(""));

  let mut start_time = Instant::now();
  loop {
    // let (tx, rx) = channel::<ProcAttribute>();

    let elapsed_time = start_time.elapsed().as_secs();
    if elapsed_time < UPDATE_INTERVAL_SEC {
      std::thread::sleep(Duration::from_secs(
        UPDATE_INTERVAL_SEC - elapsed_time,
      ));
    }
    start_time = Instant::now();

    let mut proc_invoker = invoke_process_with(
      Command::new("ps"),
      vec!["-eo", "pid,%cpu,%mem,pri,comm"], // NOTE: `pcpu == %cpu` -> `p` stands for percentage.
    )
    .unwrap();
    proc_invoker.wait()?;

    // NOTE: Over-complicated as described on the `process_collector.rs`.
    let output =
      convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())?;
    redirect_procs_stat_to_file(output, Path::new(""));

    // NOTE: Open the stats file simultaneously.
    let stat_file = File::open(FILE_NAME).expect("Failed to open stats file");

    // NOTE: Mapping the raw string data into a `ProcAttribute` structure.
    let proc_attr = ProcAttribute::new(0, 0., 0., 0, "");
    let procs_stat_vec = Vec::<ProcAttribute>::new();
    proc_attr.mapping_attr_from(stat_file, &procs_stat_vec);

    // let procs: Box<dyn std::any::Any> = Box::new(procs_stat_vec.clone());

    // let procs = match procs.downcast::<Vec<ProcAttribute>>() {
    //   Ok(procs) => procs,
    //   Err(why) => panic!("{:?}", why.as_ref()),
    // };
    // let procs_stat_vec = procs.into_boxed_slice().into_vec();
    // println!(
    //   "INFO: {:?} processes counter, at {:?}",
    //   procs_stat_vec.clone().into_boxed_slice().into_vec().len(),
    //   process_collector::date_time_helper().unwrap(),
    // );

    let (host, port) = ("127.0.0.1", 9999);
    let addr = format!("{}:{}", host, port);
    let listener = TcpListener::bind(addr).unwrap();
    println!(
      "INFO: Server hosted at address {:?}, {:?}",
      listener.local_addr().unwrap(),
      date_time_helper().unwrap()
    );

    for stream in listener.incoming() {
      let mut buffer = [0; 1024];
      let mut response = String::from("HTTP/1.1 200 OK \r\n");
      response.push_str("Access-Control-Allow-Origin: *\r\n");
      response.push_str("Connection: Keep-Alive\r\n");
      response.push_str("Content-Type: application/json\r\n");
      response.push_str("\r\n");

      match stream {
        Ok(mut stream) => loop {
          stream.read(&mut buffer)?;
          let json_response = match serde_json::to_string(&procs_stat_vec) {
            Ok(response) => response + "\r\n",
            Err(_) => "[]".to_string(),
          };
          response.push_str(&json_response);
          stream.write_all(response.as_bytes())?;
          stream.flush().unwrap();
        },
        Err(e) => {
          println!("Error: {}", e);
        }
      }
    }

    // let wrapper = Arc::new(Mutex::new(tx));
    // let procs_data_aggregate = std::thread::spawn(move || {
    //   for proc_data in procs_stat_vec {
    //     let (tx, proc_data) =
    //       (wrapper.lock().unwrap(), Arc::new(Mutex::new(proc_data)));
    //     let mut lock_data = proc_data.lock().unwrap();
    //     *lock_data += ProcAttribute::new(0, 0., 0., 0, "");
    //     tx.send(lock_data.to_owned()).unwrap();
    //   }
    // });

    // serve_process_stats_from("127.0.0.1", 9999, procs_stat_vec)
    //   .unwrap_or_default();
    // procs_data_aggregate.join().unwrap();
    std::thread::sleep(Duration::from_secs(5));
  }
}
