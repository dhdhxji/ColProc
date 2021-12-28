#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h>
#include <stdint.h>
#include "colproc/defs.h"

class Canvas
{
public:
    Canvas(size_t w, size_t h);

    virtual size_t getW();
    virtual size_t getH();

    virtual void setPix(size_t x, size_t y, ColRGB col) = 0;
    virtual ColRGB getPix(size_t x, size_t y) = 0;
    virtual ~Canvas() = 0;

protected:
    size_t _w;
    size_t _h;
};

#endif // CANVAS_H
