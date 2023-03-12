#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap.h>

extern void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

#endif