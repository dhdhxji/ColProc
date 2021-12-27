#ifndef COLPROC_GENERATOR_H
#define COLPROC_GENERATOR_H

#include "../colproc.h"

class ColProcGen: public ColProc
{
public:
    virtual void generate(
        uint32_t time, 
        color_t* colors,
        size_t count
    ) = 0;

    void get_colors(
        uint32_t time,
        color_t* colors, 
        size_t cnt
    ) {
        generate(time, colors, cnt);
    }
};


#endif // COLPROC_GENERATOR_H
