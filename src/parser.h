#ifndef PARSER_H
#define PARSER_H

#include <pcap.h>
#include <stdint.h>

typedef struct {
    char src_ip[16];
    char dst_ip[16];
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t flags;
    int is_tcp;
} packet_info;

void parse_packet(const u_char *packet, packet_info *info);

#endif