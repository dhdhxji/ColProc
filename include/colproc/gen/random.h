#ifndef RANDOM_H
#define RANDOM_H

#include "generator.h"
#include "../util/util.h"

class GeneratorRandom: public Generator
{
public:
    GeneratorRandom(uint32_t period) {
        _period = period;
    }

    void generate(
        int16_t off_x,
        int16_t off_y,
        uint32_t time, 
        Canvas* canvas
    ) override {
        time = time / _period;

        for(size_t i = 0; i < canvas->getH()*canvas->getW(); ++i) {
            uint32_t h = hash((time+1)*(i+1) + 1, 0, 360);
            uint32_t s = hash((time+1)*(i+1) + 2, 90, 100);
            uint32_t v = 100;
            
            size_t y = i / canvas->getW();
            size_t x = i % canvas->getW();

            uint8_t r, g, b;
            hsv2rgb(h, s, v, &r, &g, &b);
            
            canvas->setPix(x, y, ColRGB(r, g, b));
        }
    }

protected: 
    uint32_t _period;
};



#endif // RANDOM_H
