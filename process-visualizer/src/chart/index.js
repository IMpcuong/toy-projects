// deno-fmt-ignore-file
// deno-lint-ignore-file
// This code was bundled using `deno bundle` and it's not recommended to edit it manually

const PROC_API = "http://localhost:9999";
async function collectProcessStats(scheme, host, port) {
  let endpoint = new String();
  if (scheme && host && port) {
    endpoint = scheme.concat("://" + host + ":" + port.toString());
  } else {
    endpoint = PROC_API;
  }
  const response = await fetch(endpoint.toString());
  const result = response.ok ? await response.text() : response.statusText;
  return result;
}
let rawProcStats = "";
async function intermediatePassValue() {
  rawProcStats = await collectProcessStats("http", "localhost", 9999);
};
intermediatePassValue();
class Conversion extends Object {
  static castToSpecifiedObject(json) {
    return JSON.parse(json);
  }
  static uncastFromSpecifiedObject(json) {
    return JSON.stringify(json, undefined, 2);
  }
}
const procStats = Conversion.castToSpecifiedObject(rawProcStats);
const pidList = new Set();
Array.from(procStats).forEach((proc) => {
  pidList.add(proc.pid);
  console.log(`${proc.pid}: ${proc.memory} / ${proc.execution}`);
});
let lenPidList = 0;
pidList.forEach((_) => {
  lenPidList++;
});
lenPidList != procStats.length ? console.log(`${lenPidList} != ${procStats.length} => Inadequate!`) : console.log("Identical");
const labels = [];
const memUsage = [];
Array.from(procStats.map((p) => {
  labels.push(p.execution.split("/")[0]);
  memUsage.push(p.memory);
}));
const canvas = document.querySelector("#proc-chart");
const [chartWidth, chartHeight] = [
  canvas.width,
  canvas.height
];
const barWidth = chartWidth / procStats.length;
const maxMemUsage = Math.max(...memUsage);
const ctx = canvas.getContext("2d");
ctx.fillStyle = "blue";
for (let i = 0; i < procStats.length; i++) {
  const barHeight = memUsage[i] / maxMemUsage * chartHeight;
  const x = i * barWidth;
  const y = chartHeight - barHeight;
  ctx.fillRect(x, y, barWidth, barHeight);
}
ctx.fillStyle = "black";
ctx.font = "12px Arial";
for (let i = 0; i < labels.length; i++) {
  const x = i * barWidth + barWidth / 2;
  const y = chartHeight - 5;
  ctx.fillText(labels[i], x, y);
}
