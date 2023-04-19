use std::fmt::{self, Display};
use std::fs::File;
use std::io::{prelude::*, BufReader, Write};
use std::path::Path;
use std::process::{Command, Stdio};

type Result<T> = std::result::Result<T, ErrorWrapper>;

#[derive(Debug)]
pub enum ErrorWrapper {
  IO(std::io::Error),
  Runtime(std::fmt::Error),
  None,
}

impl std::error::Error for ErrorWrapper {}

impl Display for ErrorWrapper {
  fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    match self {
      Self::IO(e) => write!(f, "{e}"),
      Self::Runtime(e) => write!(f, "{e}"),
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
  fn new(
    pid: usize,
    cpu: f32,
    memory: f32,
    priority: u8,
    execution: &'invoke str,
  ) -> Self {
    Self { pid, cpu, memory, priority, execution }
  }

  fn mapping_attr(mut self, _stat_file: File) -> Self {
    self.pid = 0;
    self.cpu = 0 as f32;
    self.memory = 0 as f32;
    self.priority = 0;
    self.execution = "";
    self
  }
}

type ChildProc = std::process::Child;

fn invoke_process_with(mut cmd: Command, args: Vec<&str>) -> Result<ChildProc> {
  let child_proc = match cmd.args(args).stdout(Stdio::piped()).spawn() {
    Err(why) => panic!("{}", why),
    // NOTE: Over-complicated the return type here for not wasting
    //  the custom ErrorWrapper type alias.
    Ok(new_proc) => Ok(new_proc),
  };
  child_proc
}

fn convert_process_stat_to_string<T>(reader: T) -> std::io::Result<String>
where
  T: Read,
{
  let mut buf_reader = BufReader::new(reader);
  let mut proc_content = String::new();
  buf_reader.read_to_string(&mut proc_content)?;
  Ok(proc_content)
}

fn redirect_procs_stat_to_file<T>(stat: T, mut path: &Path)
where
  T: 'static + std::fmt::Debug + ToString,
{
  const FILE_NAME: &str = "./proc_stat.txt";
  let default_path = Box::new(Path::new(FILE_NAME));
  if path.to_str() == Some("") {
    unsafe {
      path = *Box::into_raw(default_path);
    }
  }

  let mut stat_file = match File::create(path) {
    Err(why) => panic!("ERROR: Couldn't open {}: {}", path.display(), why),
    Ok(opened) => opened,
  };

  match stat_file.write_all(stat.to_string().as_bytes()) {
    Err(why) => panic!("Error: Couldn't write to {}: {}", path.display(), why),
    Ok(_) => println!("INFO: Successfully wrote to {}", path.display()),
  }
}

fn main() -> std::io::Result<()> {
  let proc_attrs = ProcAttribute::new(1, 1., 1., 1, "");
  println!("{:?}", proc_attrs.to_owned());

  let mut proc_invoker = invoke_process_with(
    Command::new("ps"),
    vec!["-eo", "pid,pcpu,pmem,pri,comm"],
  )
  .unwrap();

  // NOTE: Over-complicated as described above.
  let output =
    convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())?;
  proc_invoker.wait()?;

  redirect_procs_stat_to_file(output, Path::new(""));

  Ok(())
}
