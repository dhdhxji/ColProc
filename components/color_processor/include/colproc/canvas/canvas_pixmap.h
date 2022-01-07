#ifndef CANVAS_PIXMAP_H
#define CANVAS_PIXMAP_H

#include "colproc/canvas/canvas.h"
#include <stdexcept>
#include <map>
#include <functional>

class CanvasPixMap: public Canvas {
public:
    struct Pos {
        uint16_t x;
        uint16_t y;

        Pos(uint16_t x, uint16_t y) {
            Pos::x = x;
            Pos::y = y;
        }

        bool operator<(const Pos& other) const {
            return y < other.y || (y == other.y && x < other.x);
        }
    };
    
    CanvasPixMap(size_t w, size_t h): Canvas(w, h) {}
    virtual ~CanvasPixMap() {}

    virtual void setPix(size_t x, size_t y, ColRGB col) {
        if(col == ColRGB(0, 0, 0)) {
            /* auto it = _pixmap.find(Pos(x, y));
            if(it == _pixmap.end()) {
                return;
            } else {
                //it.erase();
            } */
            _pixmap.erase(Pos(x, y));
            return;
        }

        _pixmap.insert(std::make_pair(Pos(x, y), col));
    };

    virtual ColRGB getPix(size_t x, size_t y) const override {
        auto it = _pixmap.find(Pos(x, y));
        if(it != _pixmap.end()) {
            return it->second;
        } else {
            return ColRGB(0, 0, 0);
        }
    };

    virtual void display() const override {
        throw std::runtime_error("CanvasPixMax: display call not allowed");
    }

    void traverseSetPixels(std::function<void(uint16_t, uint16_t)> cb) {
        for(auto it: _pixmap) {
            cb(it.first.x, it.first.y);
        }
    }

protected:
    std::map<Pos, ColRGB> _pixmap;
};

#endif // CANVAS_PIXMAP_H
