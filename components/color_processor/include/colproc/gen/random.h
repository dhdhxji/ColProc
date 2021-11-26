#ifndef RANDOM_H
#define RANDOM_H

#include "generator.h"
#include "../util/util.h"

class ColProcGenRandom: public ColProcGen
{
public:
    ColProcGenRandom(uint32_t period) {
        _period = period;
    }

    void generate(
        uint32_t time, 
        color_t* colors,
        size_t count
    ) {
        time = time / _period;

        for(size_t i = 0; i < count; ++i) {
            uint32_t h = hash((time+1)*(i+1) + 1, 0, 360);
            uint32_t s = hash((time+1)*(i+1) + 2, 90, 100);
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
    uint32_t _period;
};



#endif // RANDOM_H
