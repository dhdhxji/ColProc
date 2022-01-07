#ifndef COLPROC_GENERATOR_H
#define COLPROC_GENERATOR_H

#include "../colproc.h"

class Generator: public ColProc
{
public:
    virtual void generate(
        int16_t off_x,
        int16_t off_y,
        uint32_t time, 
        Canvas* canvas
    ) = 0;

    void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) override {
        generate(off_x, off_y, time, canvas);
    }
};


#endif // COLPROC_GENERATOR_H
