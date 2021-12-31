#ifndef RAINBOW_H
#define RAINBOW_H

#include "generator.h"
#include "../util/util.h"

class ColProcGenRainbow: public ColProcGen
{
public:
    ColProcGenRainbow(
        size_t length,
        size_t angle,
        uint32_t cycle_period_ms
    ) {
        _length = length;
        _angle = angle;
        _cycle_period_ms = cycle_period_ms;
    }

    void generate(
        uint32_t time, 
        Canvas* canvas
    ) {
        time = (time*360)/_cycle_period_ms;

        for(size_t x = 0; x < canvas->getW(); ++x) {
            for(size_t y = 0; y < canvas->getH(); ++y) {
                uint32_t h = (time+x*360/_length+y*_angle)%360;
                uint32_t s = 100;
                uint32_t v = 100;

                ColRGB col;
                hsv2rgb(h, s, v, &col.r, &col.g, &col.b);
                canvas->setPix(x, y, col);
            }
        }
    }

protected:
    size_t _length;
    size_t _angle;
    uint32_t _cycle_period_ms;    
};

#endif // RAINBOW_H
