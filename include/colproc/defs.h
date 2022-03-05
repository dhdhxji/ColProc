#ifndef COLPROC_DEFS_H
#define COLPROC_DEFS_H

#include <stdint.h>

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

    bool operator==(const ColRGB& o) {
        return  r == o.r && 
                g == o.g && 
                b == o.b;
    }

    ColRGB operator*(const ColRGB& other) {
        return ColRGB(
            (r * other.r)/255,
            (g * other.g)/255,
            (b * other.b)/255
        );
    }
};

#endif // COLPROC_DEFS_H
