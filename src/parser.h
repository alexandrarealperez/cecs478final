#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

typedef struct {
    char src_ip[64];
    char dst_ip[64];
    uint16_t src_port;
    uint16_t dst_port;
    int syn_flag;
    int ack_flag;
} packet_info;

int parse_packet(const unsigned char *packet, packet_info *info);

#endif