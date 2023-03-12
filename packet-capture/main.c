#include "main.h"

void detect_device_guid(char *cmd, char *storage)
{
  if (!strlen(cmd))
    printf("Error: Command syntax/arguments incorrect!\n");
  FILE *pipe = _popen(cmd, "rt");
  if (!pipe)
    printf("Error: Failed to execute command!\n");

  char ps_buffer[1024];
  while (fgets(ps_buffer, sizeof(ps_buffer), pipe))
    puts(ps_buffer);
  storage = ps_buffer;

  int eof_val = feof(pipe);
  int exit_code = _pclose(pipe);
  if (eof_val)
    printf("Info: Process returned %d\n", exit_code);
  else
    printf("Error: Failed to read the pipe to the end.\n");
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
  printf("Packet captured with length: %d\n", header->len);
  printf("Take (seconds): %ld\n", header->ts.tv_sec);
}

int main(void)
{
  char cmd[] = {"wmic nic get guid"};
  char *output = "";
  detect_device_guid(cmd, output);
  printf("%s\n", output);
}