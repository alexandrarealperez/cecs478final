#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "detector.h"
#include "logger.h"

int packet_count = 0;

void handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    packet_info info;

    parse_packet(packet, &info);
    detect(&info);

    packet_count++;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <pcap>\n", argv[0]);
        return 1;
    }

    system("mkdir -p artifacts/release/logs");
    system("mkdir -p artifacts/release/metrics");

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], errbuf);

    if (!handle) {
        printf("Error: %s\n", errbuf);
        return 1;
    }

    printf("[*] Starting analysis...\n");
    pcap_loop(handle, 0, handler, NULL);

    printf("[*] Total packets: %d\n", packet_count);

    write_metrics(packet_count);

    pcap_close(handle);
    return 0;
}