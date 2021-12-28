#ifndef COLPROC_DEFS_H
#define COLPROC_DEFS_H

#include <stdint.h>

typedef struct {
    uint8_t g;
    uint8_t r;
    uint8_t b;
} color_t;


struct ColRGB {   
    uint8_t r;
    uint8_t g;
    uint8_t b;

    ColRGB() {
        r = 0;
        g = 0;
        b = 0;
    }

    ColRGB(uint8_t _r, uint8_t _g, uint8_t _b) {
        r = _r;
        g = _g;
        b = _b;
    }
};

#endif // COLPROC_DEFS_H
