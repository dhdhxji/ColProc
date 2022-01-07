#include "colproc/canvas/canvas.h"

Canvas::Canvas(size_t w, size_t h) {
    _w = w;
    _h = h;
}

size_t Canvas::getW() const {
    return _w;
}

size_t Canvas::getH() const {
    return _h;
}

void Canvas::traverse(std::function<void(uint16_t, uint16_t)> cb) const {
    for(uint16_t x = 0; x < getW(); ++x) {
        for(uint16_t y = 0; y < getH(); ++y) {
            cb(x, y);
        }
    }
}

Canvas::~Canvas() {
}