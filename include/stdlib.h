#ifndef NORD_STDLIB_H
#define NORD_STDLIB_H

#include "nord_runtime.h"

#define RANGE_MAX 1000000

int range_count;
int range_current;

void range_init(int start, int end) {
    range_count = end - start;
    range_current = start;
}

int range_next() {
    if (range_count > 0) {
        int val = range_current;
        range_current++;
        range_count--;
        return val;
    }
    return -1;
}

#endif