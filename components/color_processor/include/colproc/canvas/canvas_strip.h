#ifndef CANVAS_STRIP_H
#define CANVAS_STRIP_H

#include "colproc/canvas/canvas.h"

class CanvasStrip: public Canvas 
{
public:
    struct color_grb_t {
        uint8_t g;
        uint8_t r;
        uint8_t b;

        color_grb_t(ColRGB col) {
            r = col.r;
            g = col.g;
            b = col.b;
        }

        operator ColRGB() {
            return ColRGB(r, g, b);
        }
    };

    enum strip_mode_t {
        MODE_CONTINUOUS,
        MODE_ZIGZAG
    };


    CanvasStrip(size_t w, size_t h, strip_mode_t mode);
    virtual ~CanvasStrip() override;

    virtual void setPix(size_t x, size_t y, ColRGB col) override;
    virtual ColRGB getPix(size_t x, size_t y) override;

    virtual void display();

protected:
    color_grb_t* _getPixPtr(size_t x, size_t y);
    size_t _bufferSize();

    uint8_t* _color_buffer;
    strip_mode_t _mode;
};

#endif // CANVAS_STRIP_H
