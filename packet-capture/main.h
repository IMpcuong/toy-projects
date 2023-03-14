#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

extern char *detect_device_guid(char *cmd, char *str_storage);
extern char *remove_curly_braces_and_blank_lines(char *content);
extern size_t str_count_num_delim(char *_src_str, const char *delim);

typedef struct FixedSizeGUIDs
{
  size_t fixed_size;
  char **list_guids;
} FixedSizeGUIDs;
extern FixedSizeGUIDs *str_separate_with_delim(char *_src_str, const char *delim, char **next_pos);

extern void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

#endif