#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>
#include <regex.h>

extern char *detect_device_guid(char *cmd, char *str_storage);
extern char *trim_blank_lines(char *content);
extern char **append_guid_to_list(char *raw_guid);
extern void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

#endif