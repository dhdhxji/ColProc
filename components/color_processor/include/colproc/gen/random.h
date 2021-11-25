#ifndef RANDOM_H
#define RANDOM_H

#include "generator.h"
#include "../util/util.h"

class ColRpocGenRandom: public ColProcGen
{
public:
    ColRpocGenRandom(uint32_t period) {
        _period = period;
    }

    void generate(
        uint32_t time, 
        color_t* colors,
        size_t count
    ) {
        time = time / _period;

        for(size_t i = 0; i < count; ++i) {
            colors[i].g = hash(time<<20 | i<<10 | 1,  255, 255);
            colors[i].r = hash(time<<20 | i<<10 | 2,  255, 255);
            colors[i].b = hash(time<<20 | i<<10 | 3,  255, 255);
        }
    }

protected: 
    uint32_t _period;
};



#endif // RANDOM_H
