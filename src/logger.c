#include "logger.h"

#include <stdio.h>

void log_message(const char *message) {
    FILE *f = fopen("artifacts/release/logs/demo.log", "a");
    if (f) {
        fprintf(f, "%s\n", message);
        fclose(f);
    }

    printf("%s\n", message);
}

void log_alert(const char *message) {
    FILE *f = fopen("artifacts/release/logs/demo.log", "a");
    if (f) {
        fprintf(f, "[ALERT] %s\n", message);
        fclose(f);
    }

    printf("[ALERT] %s\n", message);
}