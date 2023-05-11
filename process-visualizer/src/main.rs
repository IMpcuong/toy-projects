mod process_collector;

use std::{
  path::Path,
  process::Command,
  thread,
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
    let elapsed_time = start_time.elapsed().as_secs();
    if elapsed_time < UPDATE_INTERVAL_SEC {
      thread::sleep(Duration::from_secs(UPDATE_INTERVAL_SEC - elapsed_time));
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

    serve_process_stats_from("127.0.0.1", 9999, FILE_NAME.to_owned())
      .unwrap_or_default();
    thread::sleep(Duration::from_secs(5));
  }
}
