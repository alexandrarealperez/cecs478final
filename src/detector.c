#include "detector.h"
#include "logger.h"
#include <stdio.h>

static int syn_count = 0;

void detect(packet_info *info) {
    // SYN flag = 0x02
    if (info->flags & 0x02) {
        syn_count++;

        if (syn_count > 10) {
            log_alert("SYN flood suspected");
        }
    }
}