#include "colproc/util/util.h"

#define A 15845
#define C 896135

uint32_t hash(uint32_t data, uint32_t out_min, uint32_t out_max) {
    return ((data * A + C) - out_min) % out_max + out_min;
}