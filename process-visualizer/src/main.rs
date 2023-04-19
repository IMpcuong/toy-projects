use std::fmt::{self, Debug, Display};
use std::fs::File;
use std::io::{prelude::*, BufReader, Write};
use std::path::Path;
use std::process::{Command, Stdio};

use regex::Regex;

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

const FILE_NAME: &str = "./proc_stat.txt";

fn read_file_ignore_first_line(src: File) -> Vec<String> {
  let reader = BufReader::new(src);
  let mut lines = Vec::new();
  let mut buffer = String::new();
  let mut first_line_skipped = false;

  for line in reader.lines() {
    let current_line = line.unwrap();
    if first_line_skipped {
      lines.push(buffer.clone());
      buffer.clear();
    } else {
      first_line_skipped = true;
    }
    buffer.push_str(&current_line);
  }

  // Push the final line to the vector if it's not empty
  if !buffer.is_empty() {
    lines.push(buffer);
  }

  lines.split_off(1)
}

#[derive(Clone, Debug)]
struct ProcAttribute {
  pid: usize,
  cpu: f32,
  memory: f32,
  priority: u8,
  execution: String,
}

impl<'invoke> ProcAttribute {
  fn new(
    pid: usize,
    cpu: f32,
    memory: f32,
    priority: u8,
    execution: &str,
  ) -> Self {
    Self { pid, cpu, memory, priority, execution: String::from(execution) }
  }

  fn mapping_attr(self, stat_file: File) -> Vec<Self> {
    let mut proc_attrs: Vec<Self> = vec![];
    let file_lines = read_file_ignore_first_line(stat_file);
    let re = Regex::new(r"\s+").unwrap();
    for line_data in file_lines {
      let words_per_line: Vec<&str> = re.split(&line_data).collect();
      if words_per_line.len() < 5 {
        continue; // NOTE: Skip invalid lines.
      }
      // FIXME: Parsing wrong attribute's index position.
      let pid = words_per_line[0].parse::<usize>().unwrap_or_default();
      let cpu = words_per_line[1].parse::<f32>().unwrap_or_default();
      let memory = words_per_line[2].parse::<f32>().unwrap_or_default();
      let priority = words_per_line[3].parse::<u8>().unwrap_or_default();
      let execution = words_per_line[4];
      let proc_obj = ProcAttribute::new(pid, cpu, memory, priority, execution);
      proc_attrs.push(proc_obj);
    }
    proc_attrs
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
  T: 'static + Debug + ToString,
{
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
  let proc_attr = ProcAttribute::new(0, 0., 0., 0, "");
  println!("{:?}", proc_attr.to_owned());

  let mut proc_invoker =
    invoke_process_with(Command::new("ps"), vec!["-eo pid,pcpu,pmem,pri,comm"])
      .unwrap();

  // NOTE: Over-complicated as described above.
  let output =
    convert_process_stat_to_string(proc_invoker.stdout.as_mut().unwrap())?;
  proc_invoker.wait()?;

  redirect_procs_stat_to_file(output, Path::new(""));

  let stat_file = match File::open(FILE_NAME) {
    Err(why) => panic!("{}", why),
    Ok(f) => f,
  };
  let procs = proc_attr.mapping_attr(stat_file);
  println!("{:?}", procs[1]);

  Ok(())
}
