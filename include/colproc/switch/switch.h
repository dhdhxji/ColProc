#ifndef SWITCH_H
#define SWITCH_H

#include "colproc/colproc.h"
#include "colproc/variable/variable.h"
#include "colproc/switch/transition.h"
#include "colproc/util/error.hpp"
#include <vector>

using namespace std::string_literals;

class Switch: public ColProc {
protected:
    ColProc* _getInput() const {
        uint32_t index = _selector->getValue();
        if(index >= _inputs.size()) {
            index = _inputs.size()-1;
        }

        return _inputs[index];
    }

public:
    Switch(
        std::vector<ColProc*> inputs,
        Variable<int32_t>* selector,
        Transition* transition
    ) {
        for(int i = 0; i < inputs.size(); ++i) {
            ERR_CHECK_NOT_NULL(inputs[i], "Switch: input ["s + std::to_string(i) + "] is NULL"s);
        }

        ERR_CHECK_NOT_NULL(selector, "Switch: selector is NULL");
        ERR_CHECK_NOT_NULL(transition, "Switch: transition is NULL");

        _inputs = inputs;
        _selector = selector;
        _transition = transition;
        _prev_select = _getInput();
    }

    virtual void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) override {
        ERR_CHECK_NOT_NULL(canvas, "Switch: canvas is NULL");
        ColProc* src = _getInput();
        if(src != _prev_select) {
            _transition->addTransition(_prev_select, src, time);
        }

        if(_transition->isComplete()) {
            src->render(off_x, off_y, time, canvas);
        } else {
            _transition->render(off_x, off_y, time, canvas);
        }
    }

protected:
    std::vector<ColProc*>   _inputs;
    Variable<int32_t>*     _selector;
    Transition*             _transition;
    ColProc*                _prev_select;
};

#endif // SWITCH_H
