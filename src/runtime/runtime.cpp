#include "colproc/runtime/runtime.h"

#include <chrono>
#include <thread>

using namespace std::chrono;

Runtime::Runtime(
    Canvas* canvas,
    ColProc* renderTree, 
    VariableStorage* varManager,
    uint32_t frameRate
) {
    _canvas = canvas;
    _renderTree = renderTree;
    _varManager = varManager;
    _frameRate = frameRate;
    _interrupted.store(false);
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