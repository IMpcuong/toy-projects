use regex::Regex;
use serde::{Deserialize, Serialize};
use std::{
  alloc::{alloc, handle_alloc_error, Layout},
  fmt::{self, Debug, Display},
  fs::File,
  io::{prelude::*, BufReader, Write},
  os::unix::prelude::OpenOptionsExt,
  path::Path,
  process::{Command, Stdio},
  sync::{Arc, Mutex},
};

#[warn(unused_macros)]
macro_rules! _static_slice {
  ($_type:ty: $($item:expr),*) => ({
    static STATIC_SLICE: &'static [$_type] = &[$($item),*];
    STATIC_SLICE
  });
}

pub(crate) type Result<T> = std::result::Result<T, ErrorWrapper>;

#[derive(Debug)]
pub enum ErrorWrapper {
  IO(std::io::Error),
  Runtime(std::fmt::Error),
  #[allow(dead_code)]
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

impl From<std::fmt::Error> for ErrorWrapper {
  fn from(e: std::fmt::Error) -> Self {
    Self::Runtime(e)
  }
}

pub const FILE_NAME: &str = "./proc_stat.txt";

pub fn read_file_ignore_first_line(src: File) -> Vec<String> {
  let reader = BufReader::new(src);
  let mut lines = Vec::new();
  let mut buffer = String::new();

  for line in reader.lines() {
    let current_line = line.unwrap();
    buffer.clear();
    buffer.push_str(&current_line);
    lines.push(buffer.clone());
  }

  // Push the final line to the vector if it's not empty
  if !buffer.is_empty() {
    lines.push(buffer);
  }

  if lines.len() > 1 {
    return lines.split_off(1);
  }
  lines
}

pub(crate) static mut DATA_PROCESSES: Vec<ProcAttribute> = vec![];

lazy_static::lazy_static! {
  // NOTE: `Arc` := Atomically Reference Counted.
  pub(crate) static ref DATA_MUTEX: Arc<Mutex<&'static Vec<ProcAttribute>>> = Arc::new(Mutex::new(
    unsafe { &DATA_PROCESSES }
  ));
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct ProcAttribute {
  pub(crate) pid: usize,
  pub(crate) cpu: f32,
  pub(crate) memory: f32,
  pub(crate) priority: u8,
  pub(crate) execution: String,
}

impl ProcAttribute {
  pub fn new(
    pid: usize,
    cpu: f32,
    memory: f32,
    priority: u8,
    execution: String,
  ) -> Self {
    Self { pid, cpu, memory, priority, execution }
  }

  pub fn mapping_attr_from(stat_line_data: String) -> Self {
    let re = Regex::new(r"\s+").unwrap();
    let words_per_line: Vec<&str> = re.split(&stat_line_data).collect();
    if words_per_line.len() < 5 {
      return ProcAttribute::new(0, 0., 0., 0, "".to_string()); // NOTE: Skip invalid lines.
    }

    let pid = words_per_line[0].parse::<usize>().unwrap_or_default();
    let cpu = words_per_line[1].parse::<f32>().unwrap_or_default();
    let memory = words_per_line[2].parse::<f32>().unwrap_or_default();
    let priority = words_per_line[3].parse::<u8>().unwrap_or_default();
    let execution = words_per_line[4];
    let proc_obj =
      ProcAttribute::new(pid, cpu, memory, priority, execution.to_string());
    proc_obj
  }

  pub fn manual_alloc_process(self) -> Self {
    unsafe {
      let layout = Layout::new::<Self>();
      let procs_attrs_ptr = alloc(layout);
      if procs_attrs_ptr.is_null() {
        handle_alloc_error(layout);
      }
      (procs_attrs_ptr as *mut Self).write(self);
      return std::ptr::read(procs_attrs_ptr as *const Self);
    }
  }

  pub fn assign_to_global_var(procs_stat_vec: Vec<Self>) {
    unsafe {
      let mut guard = DATA_MUTEX.lock().unwrap();
      DATA_PROCESSES = Box::leak(procs_stat_vec.into_boxed_slice()).into();
      println!("=====> Assign {:#?}", DATA_PROCESSES);
      *guard = &DATA_PROCESSES;
    }
  }
}

impl std::ops::Add for ProcAttribute {
  type Output = ProcAttribute;

  fn add(self, rhs: ProcAttribute) -> Self {
    ProcAttribute {
      pid: self.pid + rhs.pid,
      cpu: self.cpu + rhs.cpu,
      memory: self.memory + rhs.memory,
      priority: self.priority,
      execution: self.execution,
    }
  }
}

impl std::ops::AddAssign for ProcAttribute {
  fn add_assign(&mut self, rhs: Self) {
    self.pid += rhs.pid;
    self.cpu += rhs.cpu;
    self.memory += rhs.memory;
  }
}

impl Default for ProcAttribute {
  fn default() -> Self {
    Self {
      pid: Default::default(),
      cpu: Default::default(),
      memory: Default::default(),
      priority: Default::default(),
      execution: Default::default(),
    }
  }
}

pub type ChildProc = std::process::Child;

pub fn invoke_process_with(
  mut cmd: Command,
  args: Vec<&str>,
) -> Result<ChildProc> {
  let child_proc = match cmd.args(args).stdout(Stdio::piped()).spawn() {
    Err(why) => panic!("{}", why),
    // NOTE: Over-complicated the return type here for not wasting
    //  the custom ErrorWrapper type alias.
    Ok(new_proc) => Ok(new_proc),
  };
  child_proc
}

pub fn convert_process_stat_to_string<T>(reader: T) -> std::io::Result<String>
where
  T: Read + Sync,
{
  let mut buf_reader = BufReader::new(reader);
  let mut proc_content = String::new();
  buf_reader.read_to_string(&mut proc_content)?;
  Ok(proc_content)
}

pub fn redirect_procs_stat_to_file<T>(stat: T, mut path: &'static Path)
where
  T: 'static + Debug + Send + Sync + ToString,
{
  let proc_stat_data = stat.to_string();
  let default_path = Box::new(Path::new(FILE_NAME));
  if let Some("") = path.to_str()
  /* Syntax equivalent with: `if path.to_str() == Some("")` */
  {
    unsafe {
      path = *Box::into_raw(default_path);
    }
  }

  if path.exists() {
    let mut existed = std::fs::OpenOptions::new()
      .truncate(true)
      .write(true)
      .create(false)
      .mode(0o770)
      .open(path)
      .expect("INFO: Successfully open our existing file");

    match existed.write_all(proc_stat_data.as_bytes()) {
      Err(why) => {
        panic!("Error: Couldn't write to {}: {:?}", path.display(), why)
      }
      Ok(_) => println!(
        "INFO: Successfully wrote to {}, at {:?}",
        path.display(),
        date_time_helper().unwrap()
      ),
    };
    return;
  }

  let mut stat_file = match File::create(path) {
    Err(why) => panic!("ERROR: Couldn't open {}: {}", path.display(), why),
    Ok(opened) => opened,
  };
  match stat_file.write_all(proc_stat_data.as_bytes()) {
    Err(why) => {
      panic!("Error: Couldn't write to {}: {}", path.display(), why)
    }
    Ok(_) => println!(
      "INFO: Successfully wrote to {}, at {:?}",
      path.display(),
      date_time_helper().unwrap()
    ),
  }
}

const DATETIME_FORMAT: &'static str = "%Y-%m-%d | %H:%M:%S";

pub(crate) fn date_time_helper() -> Result<String> {
  let now = chrono::Local::now();
  return Ok(format!("{}", now.format(DATETIME_FORMAT)));
}

#[cfg(test)]
mod test {
  use std::os::unix::prelude::PermissionsExt;

  use super::*;

  #[test]
  fn test_init_proc_attr() {
    let proc_attr = ProcAttribute::new(0, 0., 0., 0, "".to_string());
    assert_eq!(proc_attr.execution, "");
    assert_ne!(proc_attr.to_owned().execution, String::from("Something"));
  }

  #[test]
  fn test_redirect_procs_stat_to_file() -> std::io::Result<()> {
    let mut proc_invoker = invoke_process_with(
      Command::new("ps"),
      vec!["-eo", "pid,pcpu,pmem,pri,comm"],
    )
    .unwrap();
    let output =
      convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())?;
    proc_invoker.wait()?;
    assert_ne!(output, "");

    redirect_procs_stat_to_file(output, Path::new(""));
    assert!(File::open(FILE_NAME).unwrap().metadata().unwrap().is_file());
    assert_eq!(
      File::open(FILE_NAME)
        .unwrap()
        .metadata()
        .unwrap()
        .permissions()
        .mode()
        .to_string(),
      String::from("33188")
    );

    Ok(())
  }
}
