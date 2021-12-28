#include "colproc/canvas/canvas.h"

Canvas::Canvas(size_t w, size_t h) {
    _w = w;
    _h = h;
}

size_t Canvas::getW() {
    return _w;
}

size_t Canvas::getH() {
    return _h;
}

Canvas::~Canvas() {
}