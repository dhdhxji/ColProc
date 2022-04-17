#ifndef CONCAT_H
#define CONCAT_H

#include "colproc/colproc.h"
#include <vector>
#include "colproc/util/error.hpp"

class Concat: public ColProc {
public:
    Concat(const std::vector<ColProc*>& srcs)
    : _srcs(std::move(srcs)) {}

    virtual void render(
        int16_t off_x,
        int16_t off_y,
        uint32_t time,
        Canvas* canvas
    ) override {
        ERR_CHECK_NOT_NULL(canvas, "Concat: canvas is NULL");
        for(auto src: _srcs) {
            src->render(off_x, off_y, time, canvas);
        }
    }

protected:
    std::vector<ColProc*> _srcs;
};

#endif // CONCAT_H
