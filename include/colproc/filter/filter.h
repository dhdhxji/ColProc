#ifndef FILTER_H
#define FILTER_H

#include "../colproc.h"
#include "colproc/canvas/canvas.h"
#include "colproc/util/error.hpp"

class Filter: public ColProc 
{
public: 
    Filter(ColProc* src) {
        ERR_CHECK_NOT_NULL(src, "Filter: src is NULL");
        _src = src;
    }

    virtual void filter(
        uint32_t time, 
        Canvas* canvas
    ) = 0;

    void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) override {
        ERR_CHECK_NOT_NULL(canvas, "Filter: canvas is NULL");
        _src->render(off_x, off_y, time, canvas);
        filter(time, canvas);
    }

    void set_src(ColProc* src) {
        _src = src;
    }

private:
    ColProc* _src;
};

#endif // FILTER_H
