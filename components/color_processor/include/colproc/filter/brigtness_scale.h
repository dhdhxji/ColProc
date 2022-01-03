#ifndef BRIGTNESS_SCALE_H
#define BRIGTNESS_SCALE_H

#include "filter.h"
#include "colproc/variable/variable.h"

class ColProcFilterBrScale: public ColProcFilter
{
public: 
    ColProcFilterBrScale(ColProc* src, AbstractVariable* br_divider)
    :ColProcFilter(src) {
        _br_divider = br_divider->castToVariable<float>();
    }

    void filter(
        uint32_t time, 
        Canvas* canvas
    ) override {
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
    Variable<float>* _br_divider;
};

#endif // BRIGTNESS_SCALE_H
