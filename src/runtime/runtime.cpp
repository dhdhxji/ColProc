#include "colproc/runtime/runtime.h"
#include "colproc/runtime/map_var_storage.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

Runtime::Runtime() {
    _varManager.reset(new MapVarStorage());
    _interrupted = false;
    _frameRate = 0;
    _canvas = nullptr;
    _renderTree = nullptr; 
}

Runtime::Runtime(
    Canvas* canvas,
    ColProc* renderTree, 
    uint32_t frameRate
) {
    _varManager.reset(new MapVarStorage());
    _canvas = canvas;
    _renderTree = renderTree;
    _frameRate = frameRate;
    _interrupted.store(false);
}

Runtime::Runtime(
    Canvas* canvas,
    ColProc* renderTree,
    uint32_t frameRate,
    IVariableStorage* storage
) {
    _varManager.reset(storage);
    _canvas = canvas;
    _renderTree = renderTree;
    _frameRate = frameRate;
    _interrupted.store(false);
}

void Runtime::setCanvas(Canvas* canvas) {
    _canvas = canvas;
}

Canvas* Runtime::getCanvas() {
    return _canvas;
}

void Runtime::setRenderNode(ColProc* node) {
    _renderTree = node;
}

ColProc* Runtime::getRenderNode() {
    return _renderTree;
}

void Runtime::setFrameRate(uint32_t frameRate) {
    _frameRate = frameRate;
}

uint32_t Runtime::getFrameRate() {
    return _frameRate;
}

IVariableStorage& Runtime::getVariableManager() {
    return *_varManager;
}

Runtime::stop_reason_t Runtime::runRenderLoop() {
    _interrupted.store(false);

    const auto frameTime = microseconds(
        1000*1000 / _frameRate
    );

    for(;;) {
        if(_interrupted.load()) {
            return INTERRUPT;
        }

        const auto frameStart = system_clock::now();
        
        try {
            _varManager->updateVariables();
            _renderTree->render(
                duration_cast<milliseconds>(frameStart.time_since_epoch()).count(), 
                _canvas
            );

            _canvas->display();
            _canvas->clear();
        } catch(...) {
            return EXCEPTION;
        }

        const auto frameEnd = std::chrono::system_clock::now();
        const auto payloadTime = frameEnd - frameStart;

        std::this_thread::sleep_for( 
            (frameTime > payloadTime) ? frameTime-payloadTime : seconds(0)
        );
    }
}

void Runtime::interrupt() {
    _interrupted.store(true);
}