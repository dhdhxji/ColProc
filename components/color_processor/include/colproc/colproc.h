#ifndef COLPROC_UNIT_H
#define COLPROC_UNIT_H

#include <cstddef>
#include "defs.h"

class ColProc
{
public:
    virtual void get_colors(
        uint32_t time,
        color_t* colors, 
        size_t cnt
    ) = 0;
};

#endif // COLPROC_UNIT_H
