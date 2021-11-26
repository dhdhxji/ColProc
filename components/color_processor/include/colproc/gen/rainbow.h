#ifndef RAINBOW_H
#define RAINBOW_H

#include "generator.h"
#include "../util/util.h"

class ColProcGenRainbow: public ColProcGen
{
public:
    ColProcGenRainbow(
        size_t length,
        uint32_t cycle_period_ms
    ) {
        _length = length;
        _cycle_period_ms = cycle_period_ms;
    }

    void generate(
        uint32_t time, 
        color_t* colors,
        size_t count
    ) {
        time = (time*360)/_cycle_period_ms;

        for(size_t i = 0; i < count; ++i) {
            uint32_t h = (time+i*360/_length)%360;
            uint32_t s = 100;
            uint32_t v = 100;
    
            hsv2rgb(
                h, s, v, 
                &colors[i].r, 
                &colors[i].g, 
                &colors[i].b
            );
        }
    }

protected:
    size_t _length;
    uint32_t _cycle_period_ms;    
};

#endif // RAINBOW_H
