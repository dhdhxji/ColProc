#ifndef BRIGTNESS_SCALE_H
#define BRIGTNESS_SCALE_H

#include "filter.h"
#include "colproc/variable/variable.h"
#include "colproc/util/error.hpp"

class BrightnessScale: public Filter
{
public: 
    BrightnessScale(ColProc* src, Variable<double>* br_divider)
    :Filter(src) {
        ERR_CHECK_NOT_NULL(src, "BrightnessScale: src is NULL");
        ERR_CHECK_NOT_NULL(br_divider, "BrightnessScale: br_divider is NULL");
        _br_divider = br_divider;
    }

    void filter(
        uint32_t time, 
        Canvas* canvas
    ) override {
        ERR_CHECK_NOT_NULL(canvas, "BrightnessScale: canvas is NULL");
        if(_br_divider == 0) {return;}
        
        for(size_t y = 0; y < canvas->getH(); ++y) {
            for(size_t x = 0; x < canvas->getW(); ++x) {
                ColRGB c = canvas->getPix(x, y);
                c.r /= _br_divider->getValue();
                c.g /= _br_divider->getValue();
                c.b /= _br_divider->getValue();

                canvas->setPix(x, y, c);
            }
        }
    }

private:
    Variable<double>* _br_divider;
};

#endif // BRIGTNESS_SCALE_H
