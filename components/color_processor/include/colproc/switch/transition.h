#ifndef TRANSITION_H
#define TRANSITION_H

#include "colproc/colproc.h"
#include <queue>
#include <stdexcept>


class Transition: public ColProc {
protected:
    struct TransEntry
    {
        ColProc* from;
        ColProc* to;
        uint32_t start_time;

        TransEntry(ColProc* from, ColProc* to, uint32_t start_time) {
            TransEntry::from = from;
            TransEntry::to = to;
            TransEntry::start_time = start_time;
        }
    };
    

public:
    void addTransition(ColProc* start, ColProc* end, uint32_t time) {
        _transition_queue.push(TransEntry(start, end, time));
    }

    bool isComplete() const {
        return _transition_queue.empty(); 
    }

    virtual bool renderTransition(
        int16_t off_x,
        int16_t off_y,
        uint32_t time, 
        Canvas* canvas,
        const TransEntry& transition_ctx,
        uint32_t time_since_start
    ) = 0;

    virtual void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) override {
        if(_transition_queue.empty()) {
            throw std::runtime_error("Transition: There is no"
                "transitions to be displayed");
        }

        const TransEntry& current_trans = _transition_queue.front();

        bool isTransitionEnd = renderTransition(
            off_x, 
            off_y, 
            time,
            canvas,
            current_trans,
            time - current_trans.start_time
        );

        if(isTransitionEnd) {
            _transition_queue.pop();
        }
    }

protected:
    std::queue<TransEntry> _transition_queue;
};

#endif // TRANSITION_H
