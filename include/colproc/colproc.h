#ifndef COLPROC_UNIT_H
#define COLPROC_UNIT_H

#include <cstddef>
#include "defs.h"
#include "colproc/canvas/canvas.h"
#include "colproc/variable/variable.h"

class ColProc
{
public:
    virtual void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) = 0;

    virtual void render(
        uint32_t time,
        Canvas* canvas
    ) {
        render(0, 0, time, canvas);
    };
};

#endif // COLPROC_UNIT_H
