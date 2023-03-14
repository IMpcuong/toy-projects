#include "main.h"

#define MAX_SIZE (1 << 20)
#define MAX_SUBSTRINGS 50
#define MAX_SUBSTR_LEN 38

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

char *remove_curly_braces_and_blank_lines(char *content)
{
  static char beautified[MAX_SIZE];
  uint8_t is_blank_line = 1;
  size_t len_after_trim = 0;
  size_t i;
  for (i = 0; i < strlen(content); i++)
  {
    if ((content[i] != '{' && content[i] != '}') &&
        (content[i] != '\r' && content[i] != '\n'))
    {
      is_blank_line = 0;
      beautified[len_after_trim++] = content[i];
    }
    else if (!is_blank_line)
    {
      is_blank_line = 1;
      beautified[len_after_trim++] = '\n';
    }
  }
  beautified[len_after_trim] = '\0';
  return beautified;
}

size_t str_count_num_delim(char *_src_str, const char *delim)
{
  size_t count = 0;
  for (size_t i = 0; i < strlen(_src_str); i++)
    if (_src_str[i] == *delim)
      count++;
  return count;
}

char **str_separate_with_delim(char *_src_str, const char *delim, char **next_pos)
{
  size_t list_size = str_count_num_delim(_src_str, delim) + 1;
  char **substr_with_idx;
  substr_with_idx = malloc(list_size * (sizeof *substr_with_idx));

  char *substr = strtok_s(_src_str, delim, next_pos);
  size_t i;
  for (i = 0; i < list_size && substr != NULL; i++)
  {
    size_t substr_len = strlen(substr) + list_size;
    substr_with_idx[i] = malloc(substr_len * (sizeof substr_with_idx[i]));
    substr_with_idx[i] = substr;
    substr = strtok_s(NULL, delim, next_pos);
  }
  return substr_with_idx;
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
  printf("INFO: Packet captured with length: %d\n", header->len);
  printf("INFO: Take (seconds): %ld\n", header->ts.tv_sec);
}

int main(void)
{
  char cmd[] = {"wmic nic get guid | findstr /r /i /c:{.*}"};
  char *raw_guids;
  raw_guids = (char *)malloc(MAX_SIZE * (sizeof *raw_guids));
  raw_guids = detect_device_guid(cmd, raw_guids);
  raw_guids = remove_curly_braces_and_blank_lines(raw_guids);
  printf("%s\n", raw_guids);

  char *next_pos = NULL;
  char **guid_list = str_separate_with_delim(raw_guids, "\n", &next_pos);
  printf("%p\n", (void *)guid_list);
  size_t i;
  for (i = 0; i < 6; i++)
    // NOTE: Because the deviceID sequence contains all of these nonsense characters on Windows.
    if (strcmp("  ", guid_list[i]))
      printf("=====> %s\n", guid_list[i]);

  char *test_blank_string = "Nothing\r\n\n\ncan\tkick\nyour\tass";
  char *beautified = remove_curly_braces_and_blank_lines(test_blank_string);
  printf("1:\n%s\n2:\n%s\n", test_blank_string, beautified);

  free(guid_list);
}