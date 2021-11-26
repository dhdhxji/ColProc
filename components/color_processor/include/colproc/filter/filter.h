#ifndef FILTER_H
#define FILTER_H

#include "../colproc.h"

class ColProcFilter: public ColProc 
{
public: 
    ColProcFilter(ColProc* src) {
        _src = src;
    }

    virtual void filter(
        uint32_t time, 
        color_t* colors,
        size_t count
    ) = 0;

    void get_colors(
        uint32_t time,
        color_t* colors, 
        size_t cnt
    ) override {
        _src->get_colors(time, colors, cnt);
        filter(time, colors, cnt);
    }

    void set_src(ColProc* src) {
        _src = src;
    }

private:
    ColProc* _src;
};

#endif // FILTER_H
