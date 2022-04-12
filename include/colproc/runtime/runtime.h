#ifndef RUNTIME_H
#define RUNTIME_H

#include "colproc/colproc.h"
#include "colproc/runtime/map_var_storage.h"
#include "colproc/canvas/canvas.h"

#include <atomic>
#include <memory>

class Runtime {

public:
    enum stop_reason_t {
        RT_EXCEPTION,
        RT_INTERRUPT,
        RT_INTERNAL_ERROR
    };

    Runtime();

    Runtime(
        Canvas* canvas,
        ColProc* renderTree,
        uint32_t frameRate
    );

    void setCanvas(Canvas* canvas);
    Canvas* getCanvas();

    void setRenderNode(ColProc* node);
    ColProc* getRenderNode();

    void setFrameRate(uint32_t frameRate);
    uint32_t getFrameRate();

    IVariableStorage& getVariableManager();

    stop_reason_t runRenderLoop();
    void interrupt();

protected:
    Runtime(
        Canvas* canvas,
        ColProc* renderTree,
        uint32_t frameRate,
        IVariableStorage* storage
    );

protected:
    std::atomic_bool _interrupted;
    uint32_t _frameRate;
    Canvas* _canvas;
    ColProc* _renderTree;
    std::unique_ptr<IVariableStorage> _varManager;
};

#endif // RUNTIME_H
