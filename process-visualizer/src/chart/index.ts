const PROC_API = 'http://localhost:9999';

async function collectProcessStats(endpoint: string): Promise<string> {
  if (!endpoint)
    endpoint = PROC_API;

  const response = await fetch(endpoint);
  if (response.ok) {
    const result = await response;
    return result.text();
  }
  console.error(`ERROR: API call failed with status ${response.status}: ${response.statusText}`);
  return response.statusText;
}

collectProcessStats("");