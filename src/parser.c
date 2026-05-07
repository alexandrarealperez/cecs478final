#include "parser.h"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <string.h>

#define ETHERNET_HEADER_LEN 14

int parse_packet(const unsigned char *packet, packet_info *info) {
    const struct ip *ip_header = (const struct ip *)(packet + ETHERNET_HEADER_LEN);

    if (ip_header->ip_v != 4) {
        return -1;
    }

    if (ip_header->ip_p != IPPROTO_TCP) {
        return -1;
    }

    int ip_header_len = ip_header->ip_hl * 4;
    const struct tcphdr *tcp_header =
        (const struct tcphdr *)(packet + ETHERNET_HEADER_LEN + ip_header_len);

    memset(info, 0, sizeof(packet_info));

    inet_ntop(AF_INET, &(ip_header->ip_src), info->src_ip, sizeof(info->src_ip));
    inet_ntop(AF_INET, &(ip_header->ip_dst), info->dst_ip, sizeof(info->dst_ip));

    info->src_port = ntohs(tcp_header->th_sport);
    info->dst_port = ntohs(tcp_header->th_dport);

    info->syn_flag = (tcp_header->th_flags & TH_SYN) ? 1 : 0;
    info->ack_flag = (tcp_header->th_flags & TH_ACK) ? 1 : 0;

    return 0;
}