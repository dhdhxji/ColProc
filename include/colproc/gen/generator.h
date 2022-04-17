#ifndef COLPROC_GENERATOR_H
#define COLPROC_GENERATOR_H

#include "../colproc.h"
#include "colproc/util/error.hpp"

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
        ERR_CHECK_NOT_NULL(canvas, "Generator: colproc is NULL");
        generate(off_x, off_y, time, canvas);
    }
};


#endif // COLPROC_GENERATOR_H
