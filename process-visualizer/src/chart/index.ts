const PROC_API = 'http://localhost:9999';

async function collectProcessStats(scheme: string, host: string, port: number): Promise<string> {
  let endpoint = new String();
  if (!scheme && !host && !port) {
    endpoint = scheme.concat("://" + host + ':' + port.toString());
  } else {
    endpoint = PROC_API;
  }

  const response = await fetch(endpoint.toString());
  const result: string = response.ok ? await response.text() : response.statusText;
  return result;
}

const rawProcStats: string = await collectProcessStats("http", "localhost", 9999);

interface ProcessStat {
  pid: number,
  cpu: number,
  memory: number,
  priority: number,
  execution: string,
}

class Conversion extends Object {
  static castToSpecifiedObject<Type>(json: string): Type {
    return JSON.parse(json)
  }

  static uncasetFromSpecifiedObject<Type>(json: Type): string {
    return JSON.stringify(json, undefined, 2)
  }
}

const procStats: ProcessStat[] = Conversion.castToSpecifiedObject<ProcessStat[]>(rawProcStats);
const pidList: Set<number> = new Set();
Array.from(procStats).forEach((proc) => {
  pidList.add(proc.pid)
  console.log(`${proc.pid}: ${proc.memory} / ${proc.execution}`);
});

let lenPidList = 0;
pidList.forEach((_) => { lenPidList++; })
lenPidList != procStats.length
  ? console.log(`${lenPidList} != ${procStats.length} => Inadequate!`)
  : console.log("Identical");