#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "parser.h"
#include "detector.h"
#include "logger.h"

static int total_packets = 0;
static int syn_packets = 0;
static int ack_packets = 0;
static int non_syn_packets = 0;
static int alerts = 0;
static int alert_triggered = 0;

static const char *filter_expr = NULL;
static int syn_threshold = 0;

static void ensure_dirs(void) {
    mkdir("artifacts", 0777);
    mkdir("artifacts/release", 0777);
    mkdir("artifacts/release/logs", 0777);
    mkdir("artifacts/release/metrics", 0777);
}

static void write_metrics(void) {
    FILE *f = fopen("artifacts/release/metrics/results.json", "w");
    if (!f) {
        fprintf(stderr, "Error: could not write metrics file\n");
        return;
    }

    fprintf(f, "{\n");
    fprintf(f, "  \"total_packets\": %d,\n", total_packets);
    fprintf(f, "  \"syn_packets\": %d,\n", syn_packets);
    fprintf(f, "  \"ack_packets\": %d,\n", ack_packets);
    fprintf(f, "  \"non_syn_packets\": %d,\n", non_syn_packets);
    fprintf(f, "  \"alerts\": %d,\n", alerts);
    fprintf(f, "  \"bpf_filter\": \"%s\",\n", filter_expr);
    fprintf(f, "  \"syn_threshold\": %d,\n", syn_threshold);
    fprintf(f, "  \"detection_type\": \"SYN threshold detection\"\n");
    fprintf(f, "}\n");

    fclose(f);
}

void handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    (void)args;
    (void)header;

    packet_info info;

    if (parse_packet(packet, &info) == 0) {
        total_packets++;

        if (info.syn_flag) {
            syn_packets++;
        } else {
            non_syn_packets++;
        }

        if (info.ack_flag) {
            ack_packets++;
        }

        if (!alert_triggered && detect_syn_threshold(syn_packets, syn_threshold)) {
            alerts++;
            alert_triggered = 1;
            log_alert("SYN threshold exceeded: suspicious traffic detected");
        }
    }
}

int main(int argc, char *argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    struct bpf_program fp;
    bpf_u_int32 net = 0;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s <pcap file> <bpf filter> <syn threshold>\n", argv[0]);
        fprintf(stderr, "Example: %s artifacts/release/pcaps/test.pcap tcp 50\n", argv[0]);
        return 1;
    }

    const char *pcap_file = argv[1];
    filter_expr = argv[2];
    syn_threshold = atoi(argv[3]);

    if (syn_threshold <= 0) {
        fprintf(stderr, "Error: SYN threshold must be a positive integer\n");
        return 1;
    }

    ensure_dirs();

    log_message("[*] Starting Packet Sniffer with BPF analysis");

    char msg[256];

    snprintf(msg, sizeof(msg), "[*] Opening PCAP input: %s", pcap_file);
    log_message(msg);

    snprintf(msg, sizeof(msg), "[*] Applying BPF filter: %s", filter_expr);
    log_message(msg);

    snprintf(msg, sizeof(msg), "[*] SYN threshold configured: %d", syn_threshold);
    log_message(msg);

    handle = pcap_open_offline(pcap_file, errbuf);
    if (!handle) {
        fprintf(stderr, "Error opening PCAP: %s\n", errbuf);
        return 1;
    }

    if (pcap_compile(handle, &fp, filter_expr, 0, net) == -1) {
        fprintf(stderr, "BPF compile error: %s\n", pcap_geterr(handle));
        pcap_close(handle);
        return 1;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "BPF setfilter error: %s\n", pcap_geterr(handle));
        pcap_freecode(&fp);
        pcap_close(handle);
        return 1;
    }

    pcap_loop(handle, 0, handler, NULL);

    snprintf(msg, sizeof(msg), "[*] Total packets processed: %d", total_packets);
    log_message(msg);

    snprintf(msg, sizeof(msg), "[*] SYN packets observed: %d", syn_packets);
    log_message(msg);

    snprintf(msg, sizeof(msg), "[*] ACK packets observed: %d", ack_packets);
    log_message(msg);

    snprintf(msg, sizeof(msg), "[*] Non-SYN packets observed: %d", non_syn_packets);
    log_message(msg);

    snprintf(msg, sizeof(msg), "[*] Alerts generated: %d", alerts);
    log_message(msg);

    write_metrics();

    pcap_freecode(&fp);
    pcap_close(handle);

    return 0;
}