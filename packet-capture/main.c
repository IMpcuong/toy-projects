#include "main.h"

#define MAX_SIZE (1 << 20)

void close_pipe_status(FILE *stream)
{
  int eof_val = feof(stream);
  int exit_code = _pclose(stream);
  if (eof_val)
  {
    printf("INFO: Process returned %d\n", exit_code);
    return;
  }
  fprintf(stderr, "ERROR: Failed to read the pipe until the end.\n");
  exit(1);
}

char *detect_device_guid(char *cmd, char *str_guid)
{
  if (!strlen(cmd))
    fprintf(stderr, "ERROR: Command syntax/arguments incorrect!\n");

  FILE *pipe = _popen(cmd, "rt");
  if (!pipe)
    fprintf(stderr, "ERROR: Failed to execute command!\n");

  char ps_buffer[MAX_SIZE];
  while (fgets(ps_buffer, sizeof ps_buffer, pipe))
  {
    fputs(ps_buffer, stdout);
    strcat_s(str_guid, sizeof ps_buffer, ps_buffer);
  }
  close_pipe_status(pipe);
  return str_guid;
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

char **append_guid_to_list(char *raw_guid)
{
  static char *guid_list[3];
  regex_t reg_enable;
  regmatch_t match;
  int status;

  status = regcomp(&reg_enable, "{(?:.*)}", REG_EXTENDED);
  if (status != 0)
  {
    printf("ERROR: Compiling regular expression\n");
    exit(1);
  }
  status = regexec(&reg_enable, raw_guid, 10, &match, 0);
  if (status != 0)
  {
    printf("ERROR: No match found\n");
    exit(1);
  }
  char *matched_pattern = raw_guid + match.rm_so;
  int matched_len = match.rm_eo - match.rm_so;
  size_t i;
  for (i = 0; i < sizeof(guid_list) / sizeof(*guid_list); i++)
  {
    guid_list[i] = matched_pattern;
  }
  regfree(&reg_enable);
  return guid_list;
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
  printf("INFO: Packet captured with length: %d\n", header->len);
  printf("INFO: Take (seconds): %ld\n", header->ts.tv_sec);
}

int main(void)
{
  char cmd[] = {"wmic nic get guid"};
  char *guid_list;
  guid_list = (char *)malloc(MAX_SIZE * (sizeof *guid_list));
  guid_list = detect_device_guid(cmd, guid_list);
  guid_list = trim_blank_lines(guid_list);

  char *test_blank_string = "Nothing\r\n\n\ncan\tkick\nyour\tass";
  char *beautified = trim_blank_lines(test_blank_string);
  printf("1:\n%s\n2:\n%s\n", test_blank_string, beautified);
}