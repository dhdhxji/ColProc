#ifndef MOVE_H
#define MOVE_H

#include "colproc/colproc.h"
#include "colproc/variable/variable.h"
#include "colproc/canvas/canvas.h"
#include <cmath>


class Move: public ColProc {
public:
    Move(
        ColProc* src, 
        Variable<int32_t>* off_x, 
        Variable<int32_t>* off_y
    ) {
        _src = src;
        _off_x = off_x;
        _off_y = off_y;
    }

    virtual void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) {
        _src->render(
            _off_x->getValue() + off_x,
            _off_y->getValue() + off_y,
            time, 
            canvas
        );
    }

protected:
    ColProc* _src;
    Variable<int32_t>* _off_x; 
    Variable<int32_t>* _off_y;
};

#endif // MOVE_H
