use std::fmt::{self, Display};
use std::process::Command;

pub type Result<T> = std::result::Result<T, ErrorWrapper>;

#[derive(Debug)]
pub enum ErrorWrapper {
  IO(std::io::Error),
  RuntimeError,
  None,
}

impl std::error::Error for ErrorWrapper {}

impl Display for ErrorWrapper {
  fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    match self {
      Self::IO(e) => write!(f, "{e}"),
      Self::RuntimeError => write!(f, "Runtime error"),
      Self::None => Ok(()),
    }
  }
}

impl From<std::io::Error> for ErrorWrapper {
  fn from(e: std::io::Error) -> Self {
    Self::IO(e)
  }
}

#[derive(Clone, Copy, Debug)]
struct ProcAttribute<'invoke> {
  pid: usize,
  cpu: f32,
  memory: f32,
  priority: u8,
  execution: &'invoke str,
}

impl<'invoke> ProcAttribute<'invoke> {
  fn mapping_attr(mut self, _proc: &ChildProc) -> Self {
    self.pid = 0;
    self.cpu = 0 as f32;
    self.memory = 0 as f32;
    self
  }
}

pub type ChildProc = std::process::ChildStdout;

fn invoke_process_with(mut cmd: Command, args: &str) -> Option<ChildProc> {
  let child_proc = cmd.arg(args).spawn();
  match child_proc {
    Ok(mut c) => c.stdout.take(),
    Err(_) => None,
  }
}

fn main() {
  let proc_invoker =
    invoke_process_with(Command::new("ps"), "-eo pid,pcpu,pmem,pri,comm");
  println!("{:?}", proc_invoker);
}
