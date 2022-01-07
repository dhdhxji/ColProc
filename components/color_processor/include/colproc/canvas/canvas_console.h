#ifndef CANVAS_CONSOLE_H
#define CANVAS_CONSOLE_H

#include <stdexcept>
#include "canvas.h"

class CanvasConsole: public Canvas
{
public:
    CanvasConsole(size_t w, size_t h);
    ~CanvasConsole() override;

    void setPix(size_t x, size_t y, ColRGB col) override;
    ColRGB getPix(size_t x, size_t y) const override;

    void display() const override;

private:
    ColRGB* _canvas;
};


#endif // CANVAS_CONSOLE_H
