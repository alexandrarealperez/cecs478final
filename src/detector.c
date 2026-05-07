#include "detector.h"

int detect_syn_threshold(int syn_count, int threshold) {
    return syn_count > threshold;
}