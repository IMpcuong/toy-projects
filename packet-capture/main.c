#include "main.h"

#define MAX_SIZE (1 << 20)

char *detect_device_guid(char *cmd, char *str_storage)
{
  if (!strlen(cmd))
    fprintf(stderr, "Error: Command syntax/arguments incorrect!\n");

  FILE *pipe = _popen(cmd, "rt");
  if (!pipe)
    fprintf(stderr, "Error: Failed to execute command!\n");

  char ps_buffer[MAX_SIZE];
  while (fgets(ps_buffer, sizeof ps_buffer, pipe))
  {
    fputs(ps_buffer, stdout);
    strcat_s(str_storage, sizeof ps_buffer, ps_buffer);
  }

  int eof_val = feof(pipe);
  int exit_code = _pclose(pipe);
  if (eof_val)
    printf("Info: Process returned %d\n", exit_code);
  else
    fprintf(stderr, "Error: Failed to read the pipe until the end.\n");

  return str_storage;
}

char *trim_blank_lines(char *content)
{
  static char beautified[MAX_SIZE];
  size_t len_after_trim = 0;
  int is_blank = 1;

  size_t i;
  for (i = 0; i < strlen(content); i++)
  {
    if (content[i] != '\r' && content[i] != '\n')
    {
      is_blank = 0;
      beautified[len_after_trim++] = content[i];
    }
    else if (!is_blank)
    {
      is_blank = 1;
      beautified[len_after_trim++] = '\n';
    }
  }
  beautified[len_after_trim] = '\0';
  return beautified;
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
  printf("Packet captured with length: %d\n", header->len);
  printf("Take (seconds): %ld\n", header->ts.tv_sec);
}

int main(void)
{
  char cmd[] = {"wmic nic get guid"};
  char *output;
  output = (char *)malloc(MAX_SIZE * (sizeof *output));
  output = detect_device_guid(cmd, output);

  char *beautified = trim_blank_lines(output);
  printf("%s\n", beautified);
}