#include "colproc/colproc.h"
#include "colproc/gen/rainbow.h"
#include "colproc/gen/text.h"
#include "colproc/mod/move.h"
#include "colproc/mod/mixer.h"

#include "colproc/filter/brigtness_scale.h"
#include "colproc/variable/variable_constant.h"
#include "colproc/variable/variable_callback.h"
#include "colproc/switch/switch.h"
#include "colproc/switch/transition_simple.h"
#include "colproc/runtime/runtime.h"

#include <chrono>


#define REFRESH_RATE_HZ 60
#define MATRIX_W        19
#define MATRIX_H        7



class CanvasConsole: public Canvas
{
public:
    CanvasConsole(size_t w, size_t h): Canvas(w, h) {
        _canvas = new ColRGB[w*h];

        for(size_t i = 0; i < w*h; ++i) {
            _canvas[i].r = 0;
            _canvas[i].g = 0;
            _canvas[i].b = 0;
        } 
    }

    ~CanvasConsole() override {
        delete[] _canvas;
    }

    void setPix(size_t x, size_t y, ColRGB col) override {
        if(x >= getW() || y >= getH()) {
            throw std::runtime_error(
                std::string("Out of bounds in setPix(") + 
                std::to_string(x) + 
                ";" + 
                std::to_string(y) + 
                ")"
            );
            return;
        }
        size_t index = y*getW() + x;

        _canvas[index] = col;
    }

    ColRGB getPix(size_t x, size_t y) const override {
        if(x >= getW() || y >= getH()) { 
            throw std::runtime_error(
                std::string("Out of bounds in getPix(") + 
                std::to_string(x) + 
                ";" + 
                std::to_string(y) + 
                ")"
            );
            return ColRGB(0,0,0);
        }
        size_t index = y*getW() + x;

        return _canvas[index];
    }

    void display() const override {
        printf("\033[0;0H");
        for(size_t y = 0; y < getH(); ++y) {
            for(size_t x = 0; x < getW(); ++x) {
                ColRGB col = getPix(x, y);
                printf("\033[48;2;%d;%d;%dm ", col.r, col.g, col.b);
                printf("\033[48;2;%d;%d;%dm ", col.r, col.g, col.b);
            }
            printf("\n");
        }
    }

private:
    ColRGB* _canvas;
};



static ColProc* build_processor(const VariableStorage& storage) {
    ColProc* text = new GeneratorText(
        new VariableConstant<std::string>("07:45"),
        new VariableConstant<std::string>("3_by_57")
    );

    ColProc* moved_text = new Move(
        text,
        new VariableConstant<int16_t>(1),
        new VariableConstant<int16_t>(1)
    );

    ColProc* rainbow = new GeneratorRainbow(
        new VariableConstant<uint32_t>(50),
        new VariableConstant<uint32_t>(0),
        new VariableConstant<uint32_t>(5000)
    );
    
    ColProc* mixed_text = new Mixer(rainbow, moved_text);

    ColProc* switched = new Switch(
        {mixed_text, rainbow},
        storage.getVariable<uint32_t>("rainbow_text_select"),
        new TransitionSimple()
    );

    return new BrightnessScale(
        switched, 
        new VariableConstant<float>(1)
    );
}



int main(int argc, char** argv)
{
    VariableStorage* storage = new VariableStorage();
    storage->addVariable(
        "rainbow_text_select",
        new VariableCallback<uint32_t>(
            []() {
                uint32_t time_ms = std::chrono::milliseconds().count();
                return (time_ms/1000) % 2;
            }
        )
    );

    ColProc* processor = build_processor(*storage);
    VariableStorage varManager;

    Runtime rt(
        new CanvasConsole(MATRIX_W, MATRIX_H),
        processor,
        &varManager,
        REFRESH_RATE_HZ
    );

    auto stopReason = rt.runRenderLoop();
}