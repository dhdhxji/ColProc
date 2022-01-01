#ifndef FILTER_H
#define FILTER_H

#include "../colproc.h"
#include "colproc/canvas/canvas.h"

class Filter: public ColProc 
{
public: 
    Filter(ColProc* src) {
        _src = src;
    }

    virtual void filter(
        uint32_t time, 
        Canvas* canvas
    ) = 0;

    void get_colors(
        uint32_t time,
        Canvas* canvas
    ) override {
        _src->get_colors(time, canvas);
        filter(time, canvas);
    }

    void set_src(ColProc* src) {
        _src = src;
    }

private:
    ColProc* _src;
};

#endif // FILTER_H
