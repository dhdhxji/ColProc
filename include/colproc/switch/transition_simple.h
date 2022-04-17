#ifndef TRANSITION_SIMPLE_H
#define TRANSITION_SIMPLE_H

#include "colproc/switch/transition.h"
#include "colproc/variable/variable.h"
#include "colproc/util/error.hpp"

class TransitionSimple: public Transition {
protected: 
    virtual bool renderTransition(
        int16_t off_x,
        int16_t off_y,
        uint32_t time, 
        Canvas* canvas,
        const TransEntry& transition_ctx,
        uint32_t time_since_start
    ) override {
        ERR_CHECK_NOT_NULL(canvas, "TransitionSimple: canvas is NULL");
        transition_ctx.to->render(off_x, off_y, time, canvas);
        return true;
    }
};

#endif // TRANSITION_SIMPLE_H
