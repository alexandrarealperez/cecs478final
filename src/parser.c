#include "parser.h"
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h>

void parse_packet(const u_char *packet, packet_info *info) {
    struct ip *ip_header = (struct ip *)(packet + 14);

    strcpy(info->src_ip, inet_ntoa(ip_header->ip_src));
    strcpy(info->dst_ip, inet_ntoa(ip_header->ip_dst));

    int ip_header_len = ip_header->ip_hl * 4;
    struct tcphdr *tcp = (struct tcphdr *)(packet + 14 + ip_header_len);

    info->src_port = ntohs(tcp->source);
    info->dst_port = ntohs(tcp->dest);
    info->flags = tcp->th_flags;
}