#ifndef COLPROC_UNIT_H
#define COLPROC_UNIT_H

#include <cstddef>
#include "defs.h"
#include "colproc/canvas/canvas.h"
#include "colproc/variable/variable.h"

class ColProc
{
public:
    virtual void get_colors(
        uint32_t time,
        Canvas* canvas
    ) = 0;
};

#endif // COLPROC_UNIT_H
