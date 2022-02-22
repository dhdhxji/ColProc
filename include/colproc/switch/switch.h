#ifndef SWITCH_H
#define SWITCH_H

#include "colproc/colproc.h"
#include "colproc/variable/variable.h"
#include "colproc/switch/transition.h"
#include <vector>

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
        Variable<uint32_t>* selector,
        Transition* transition
    ) {
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
    Variable<uint32_t>*     _selector;
    Transition*             _transition;
    ColProc*                _prev_select;
};

#endif // SWITCH_H
