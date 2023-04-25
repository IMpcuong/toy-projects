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

const procStats: string = await collectProcessStats("http", "localhost", 9999);
console.log(`Process stats: ${procStats}`);