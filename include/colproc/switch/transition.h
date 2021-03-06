#ifndef TRANSITION_H
#define TRANSITION_H

#include "colproc/colproc.h"
#include "colproc/util/error.hpp"
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
            ERR_CHECK_NOT_NULL(from, "TransEntry: from is NULL");
            ERR_CHECK_NOT_NULL(to, "TransEntry: to is NULL");

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

    virtual void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) override {
        ERR_CHECK_NOT_NULL(canvas, "Transition: canvas is NULL");
        ERR_ASSERT_FALSE(_transition_queue.empty(), "Transition: There is no transitions to be displayed");

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
    virtual bool renderTransition(
        int16_t off_x,
        int16_t off_y,
        uint32_t time, 
        Canvas* canvas,
        const TransEntry& transition_ctx,
        uint32_t time_since_start
    ) = 0;

protected:
    std::queue<TransEntry> _transition_queue;
};

#endif // TRANSITION_H
