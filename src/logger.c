#include "logger.h"
#include <stdio.h>

void log_alert(const char *message) {
    FILE *f = fopen("artifacts/release/logs/alerts.log", "a");
    fprintf(f, "[ALERT] %s\n", message);
    fclose(f);
}

void write_metrics(int total_packets) {
    FILE *f = fopen("artifacts/release/metrics/results.json", "w");
    fprintf(f, "{ \"total_packets\": %d }\n", total_packets);
    fclose(f);
}