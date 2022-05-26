#include "../util/console_canvas.h"
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
#include "colproc/mod/concat.h"
#include "colproc/runtime/runtime.h"
#include "colproc/util/error.hpp"

#include <chrono>


#define REFRESH_RATE_HZ 30
#define MATRIX_W        19
#define MATRIX_H        7


using namespace std::chrono;
using namespace std::string_literals;





static ColProc* build_processor(IVariableStorage& storage) {
    storage.addVariable(
        "hrs",
        new VariableCallback<std::string>([](){
            time_t ttime = time(0);
            struct tm* tm_time = localtime(&ttime);
            return  std::to_string(tm_time->tm_hour);
        })
    );

    storage.addVariable(
        "mins",
        new VariableCallback<std::string>([](){
            time_t ttime = time(0);
            struct tm* tm_time = localtime(&ttime);
            return  std::to_string(tm_time->tm_min);
        })
    );

    ColProc* hrs = new GeneratorText(
        storage.getVariable("hrs")->castToVariable<std::string>(),
        new VariableConstant<std::string>("3_by_57")
    );

    ColProc* dash = new Move(
        new GeneratorText(
            new VariableConstant<std::string>(":"),
            new VariableConstant<std::string>("3_by_57")
        ),
        new VariableConstant<int32_t>(7),
        new VariableConstant<int32_t>(0)
    );

    ColProc* min = new Move(
        new GeneratorText(
            storage.getVariable("mins")->castToVariable<std::string>(),
            new VariableConstant<std::string>("3_by_57")
        ),
        new VariableConstant<int32_t>(10),
        new VariableConstant<int32_t>(0)
    );

    ColProc* text = new Concat({hrs, dash, min});

    ColProc* moved_text = new Move(
        text,
        new VariableConstant<int32_t>(1),
        new VariableConstant<int32_t>(1)
    );

    ColProc* rainbow = new GeneratorRainbow(
        new VariableConstant<int32_t>(50),
        new VariableConstant<int32_t>(0),
        new VariableConstant<int32_t>(5000)
    );
    
    ColProc* mixed_text = new Mixer(rainbow, moved_text);

    ColProc* switched = new Switch(
        {mixed_text, rainbow},
        storage.getVariable("rainbow_text_select")->castToVariable<int32_t>(),
        new TransitionSimple()
    );

    return new BrightnessScale(
        switched, 
        new VariableConstant<double>(1)
    );
}



int main(int argc, char** argv)
{
    CanvasConsole canvas(MATRIX_W, MATRIX_H);

    Runtime rt;
    rt.setCanvas(&canvas);
    rt.setFrameRate(REFRESH_RATE_HZ);
    
    rt.getVariableManager().addVariable(
        "rainbow_text_select",
        new VariableCallback<int32_t>(
            []() {
                int32_t time_ms = 
                    duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
                return (time_ms/1000) % 2;
            }
        )
    );

    std::unique_ptr<ColProc> node( build_processor(rt.getVariableManager()) );
    rt.setRenderNode(node.get());

    auto stopReason = rt.runRenderLoop();
}
