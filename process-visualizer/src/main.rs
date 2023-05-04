mod process_collector;

use std::{
  fs::File,
  io::prelude::*,
  net::TcpListener,
  path::Path,
  process::Command,
  time::{Duration, Instant},
};

use crate::process_collector::*;

fn main() -> std::io::Result<()> {
  let interval = Duration::from_secs(1);
  let mut start = Instant::now();

  loop {
    let now = Instant::now();
    if now - start >= interval {
      let mut proc_invoker = invoke_process_with(
        Command::new("ps"),
        vec!["-eo", "pid,pcpu,pmem,pri,comm"],
      )
      .unwrap();

      // NOTE: Over-complicated as described on the `process_collector.rs`.
      let output =
        convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())?;
      proc_invoker.wait()?;

      redirect_procs_stat_to_file(output, Path::new(""));

      let proc_attr = ProcAttribute::new(0, 0., 0., 0, "");
      let stat_file = match File::open(FILE_NAME) {
        Err(why) => panic!("{}", why),
        Ok(f) => f,
      };
      let procs: Box<dyn std::any::Any> =
        Box::new(proc_attr.mapping_attr(stat_file));

      let listener = TcpListener::bind("127.0.0.1:9999").unwrap();
      println!("INFO: Server started at http://localhost:9999");

      for stream in listener.incoming() {
        match stream {
          Ok(mut stream) => {
            let mut buffer = [0; 1024];
            stream.read(&mut buffer).unwrap();

            if let Some(procs) = procs.downcast_ref::<Vec<ProcAttribute>>() {
              let mut response = String::from("HTTP/1.1 200 OK \r\n");
              response.push_str("Access-Control-Allow-Origin: *\r\n");
              response.push_str("Connection: Keep-Alive\r\n");
              response.push_str("Content-Type: application/json\r\n");
              response.push_str("\r\n");
              let json_response = match serde_json::to_string(&procs) {
                Ok(response) => response + "\r\n",
                Err(_) => "[]".to_string(),
              };
              response.push_str(&json_response);
              stream.write(response.as_bytes()).unwrap();
              stream.flush().unwrap();
            }
          }
          Err(e) => {
            println!("Error: {}", e);
          }
        }
      }
      start = now;
    }
  }
}
