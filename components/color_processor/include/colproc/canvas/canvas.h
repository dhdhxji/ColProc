#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h>
#include <stdint.h>
#include <functional>
#include "colproc/defs.h"

class Canvas
{
public:
    Canvas(size_t w, size_t h);
    virtual ~Canvas() = 0;

    virtual size_t getW() const;
    virtual size_t getH() const;

    virtual void setPix(size_t x, size_t y, ColRGB col) = 0;
    virtual ColRGB getPix(size_t x, size_t y) const = 0;

    virtual void clear();

    void traverse(std::function<void(uint16_t, uint16_t)> cb) const;

    virtual void display() const = 0;

protected:
    size_t _w;
    size_t _h;
};

#endif // CANVAS_H
