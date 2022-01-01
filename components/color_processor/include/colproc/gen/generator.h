#ifndef COLPROC_GENERATOR_H
#define COLPROC_GENERATOR_H

#include "../colproc.h"

class Generator: public ColProc
{
public:
    virtual void generate(
        uint32_t time, 
        Canvas* canvas
    ) = 0;

    void get_colors(
        uint32_t time,
        Canvas* canvas
    ) {
        generate(time, canvas);
    }
};


#endif // COLPROC_GENERATOR_H
