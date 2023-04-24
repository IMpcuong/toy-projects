const PROC_API = 'http://localhost:9999';

async function collectProcessAPI(endpoint: string): Promise<void> {
  if (!endpoint)
    endpoint = PROC_API;

  const response = await fetch(endpoint);
  if (response.ok) {
    const result = await response;
    console.log(result);
  } else {
    console.error(`ERROR: API call failed with status ${response.status}: ${response.statusText}`);
  }
}

collectProcessAPI("");