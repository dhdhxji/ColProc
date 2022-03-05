#ifndef RUNTIME_H
#define RUNTIME_H

#include "colproc/colproc.h"
#include "colproc/runtime/variable_storage.h"
#include "colproc/canvas/canvas.h"

#include <atomic>

class Runtime {

public:
    enum stop_reason_t {
        EXCEPTION,
        INTERRUPT,
        INTERNAL_ERROR
    };

    Runtime(
        Canvas* canvas,
        ColProc* renderTree, 
        VariableStorage* varManager,
        uint32_t frameRate
    );

    stop_reason_t runRenderLoop();
    void interrupt();

protected:
    std::atomic_bool _interrupted;
    uint32_t _frameRate;

    Canvas* _canvas;
    ColProc* _renderTree;
    VariableStorage* _varManager;
};

#endif // RUNTIME_H
