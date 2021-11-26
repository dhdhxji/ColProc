#ifndef BRIGTNESS_SCALE_H
#define BRIGTNESS_SCALE_H

#include "filter.h"

class ColProcFilterBrScale: public ColProcFilter
{
public: 
    ColProcFilterBrScale(ColProc* src, uint16_t br_divider)
    :ColProcFilter(src) {
        _br_divider = br_divider;
    }

    void filter(
        uint32_t time, 
        color_t* colors,
        size_t count
    ) override {
        if(_br_divider == 0) {return;}
        for(size_t i = 0; i < count; ++i) {
            colors[i].r /= _br_divider;
            colors[i].g /= _br_divider;
            colors[i].b /= _br_divider;
        }
    }

private:
    uint16_t _br_divider;
};

#endif // BRIGTNESS_SCALE_H
