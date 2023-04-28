const PROC_API = "http://localhost:9999";

async function collectProcessStats(
  scheme: string,
  host: string,
  port: number,
): Promise<string> {
  let endpoint = new String();
  if (scheme && host && port) {
    endpoint = scheme.concat("://" + host + ":" + port.toString());
  } else {
    endpoint = PROC_API;
  }

  const response = await fetch(endpoint.toString(), { mode: "cors" });
  const result: string = response.ok
    ? await response.text()
    : response.statusText;
  return result;
}

const rawProcStats: string = await collectProcessStats(
  "http",
  "localhost",
  9999,
);

interface ProcessStat {
  pid: number;
  cpu: number;
  memory: number;
  priority: number;
  execution: string;
}

class Conversion extends Object {
  static castToSpecifiedObject<Type>(json: string): Type {
    return JSON.parse(json);
  }

  static reverseFromSpecifiedObject<Type>(json: Type): string {
    return JSON.stringify(json, undefined, 2);
  }
}

const procStats: ProcessStat[] = Conversion.castToSpecifiedObject<
  ProcessStat[]
>(rawProcStats);
const pidList: Set<number> = new Set();
Array.from(procStats).forEach((proc) => {
  pidList.add(proc.pid);
  console.log(`${proc.pid}: ${proc.memory} / ${proc.execution}`);
});

let lenPidList = 0;
pidList.forEach((_) => {
  lenPidList++;
});
lenPidList != procStats.length
  ? console.log(`${lenPidList} != ${procStats.length} => Inadequate!`)
  : console.log("Identical");

const labels: Array<string> = [];
const memUsage: Array<number> = [];
Array.from(procStats.map((p) => {
  labels.push(
    p.execution.includes("/") ? p.execution.split("/")[1] : p.execution,
  );
  memUsage.push(p.memory);
}));
console.log(labels);
console.log(memUsage);

const canvas = document.querySelector("#proc-chart") as HTMLCanvasElement;
const [chartWidth, chartHeight] = [canvas.width, canvas.height];
const barWidth = chartWidth / procStats.length;
const maxMemUsage = Math.max(...memUsage);

const ctx = canvas.getContext("2d");
ctx!.fillStyle = "blue"; // NOTE: To fix the error `The left-hand side of an assignment expression may not be an optional property access.`
for (let i = 0; i < procStats.length; i++) {
  const barHeight = (memUsage[i] / maxMemUsage) * chartHeight;
  const x = i * barWidth;
  const y = chartHeight - barHeight;
  ctx!.fillRect(x, y, barWidth, barHeight);
}

ctx!.fillStyle = "black";
ctx!.font = "12px Arial";
for (let i = 0; i < labels.length; i++) {
  const x = i * barWidth + barWidth / 2;
  const y = chartHeight - 5;
  ctx!.fillText(labels[i], x, y);
}
