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
  println!(
    "{:?}",
    ProcAttribute::manual_alloc_process(ProcAttribute {
      pid: 10,
      cpu: 10.01,
      memory: 12.21,
      priority: 10,
      execution: String::from("")
    })
  );

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
    let elapsed_time = start_time.elapsed().as_secs();
    if elapsed_time < UPDATE_INTERVAL_SEC {
      std::thread::sleep(Duration::from_secs(
        UPDATE_INTERVAL_SEC - elapsed_time,
      ));
    }
    start_time = Instant::now();

    let (host, port) = ("127.0.0.1", 9999);
    let addr = format!("{}:{}", host, port);
    let listener = TcpListener::bind(addr).unwrap();
    println!(
      "INFO: Server hosted at address {:?}, {:?}",
      listener.local_addr().unwrap(),
      date_time_helper().unwrap()
    );

    std::thread::spawn(move || {
      loop {
        let mut proc_invoker = invoke_process_with(
          Command::new("ps"),
          vec!["-eo", "pid,%cpu,%mem,pri,comm"], // NOTE: `pcpu == %cpu` -> `p` stands for percentage.
        )
        .unwrap();
        proc_invoker.wait().unwrap();

        // NOTE: Over-complicated as described on the `process_collector.rs`.
        let output =
          convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())
            .unwrap_or_default();
        redirect_procs_stat_to_file(output, Path::new(""));

        std::thread::sleep(std::time::Duration::from_secs(1));
        // NOTE: Open the stats file simultaneously.
        let stat_file =
          File::open(FILE_NAME).expect("Failed to open stats file");

        // NOTE: Mapping the raw string data into a `ProcAttribute` structure.
        let mut procs_stat_vec = Vec::<ProcAttribute>::new();
        let file_lines =
          read_file_ignore_first_line(stat_file.try_clone().unwrap());
        for stat_line_data in file_lines {
          let stat_line_data = stat_line_data.trim_start();
          let proc_data =
            ProcAttribute::mapping_attr_from(stat_line_data.to_string());
          procs_stat_vec.push(proc_data);
        }

        // NOTE: Experimental `Box` heap allocator feature for our implementation.
        let procs: Box<dyn std::any::Any> = Box::new(procs_stat_vec.clone());

        let procs = match procs.downcast::<Vec<ProcAttribute>>() {
          Ok(procs) => procs,
          Err(why) => panic!("{:?}", why.as_ref()),
        };
        let procs_stat_vec = procs.into_boxed_slice().into_vec();
        println!(
          "INFO: {:?} processes counter, at {:?}",
          procs_stat_vec.clone().into_boxed_slice().into_vec().len(),
          process_collector::date_time_helper().unwrap(),
        );

        // NOTE: Accessing the entire collector's stats data to prevent data corruption/intersection/intervention.
        ProcAttribute::assign_to_global_var(procs_stat_vec);
        std::thread::sleep(std::time::Duration::from_secs(1));
      }
    });

    // NOTE: Using `lazy_static` crate to avoid redundant initialization variables with static lifetime.
    let guard = DATA_MUTEX.lock().unwrap();
    let procs_stat_vec_clone = *guard;
    println!("=====> Clone {:?}", procs_stat_vec_clone);

    for stream in listener.incoming() {
      let mut buffer = [0; 1024];
      let mut response = String::from("HTTP/1.1 200 OK \r\n");
      response.push_str("Access-Control-Allow-Origin: *\r\n");
      response.push_str("Connection: Keep-Alive\r\n");
      response.push_str("Content-Type: application/json\r\n");
      response.push_str("\r\n");

      match stream {
        Ok(mut stream) => {
          stream.read(&mut buffer)?;

          let json_response = match serde_json::to_string(&procs_stat_vec_clone)
          {
            Ok(response) => response + "\r\n",
            Err(_) => "[]".to_string(),
          };
          println!("=====> Response {}", json_response);
          response.push_str(&json_response);
          stream.write_all(response.as_bytes())?;
          stream.flush().unwrap();
        }
        Err(e) => {
          println!("Error: {}", e);
        }
      }
    }
    std::thread::sleep(Duration::from_secs(5));
  }
}
