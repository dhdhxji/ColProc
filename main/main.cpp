#include "colproc/colproc.h"
#include "colproc/gen/rainbow.h"
#include "colproc/gen/text.h"
#include "colproc/mod/move.h"
#include "colproc/mod/mixer.h"

#include "colproc/filter/brigtness_scale.h"
#include "colproc/canvas/canvas_strip.h"
#include "colproc/canvas/canvas_console.h"
#include "colproc/variable/variable_constant.h"
#include "colproc/variable/variable_callback.h"
#include "colproc/switch/switch.h"
#include "colproc/switch/transition_simple.h"

#include "display_loop.h"

#include "esp_timer.h"

#define REFRESH_RATE_HZ 60
#define MATRIX_W        19
#define MATRIX_H        7

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


extern "C" {
    void app_main(void);
}

void app_main(void)
{
    VariableStorage* storage = new VariableStorage();
    storage->addVariable(
        "rainbow_text_select",
        new VariableCallback<uint32_t>(
            []() {
                uint32_t time_ms = esp_timer_get_time()/1000;
                return (time_ms/1000) % 2;
            }
        )
    );

    ColProc* processor = build_processor(*storage);
    display_loop_start(
        processor, 
        new CanvasStrip(
            MATRIX_W, 
            MATRIX_H, 
            CanvasStrip::MODE_ZIGZAG, 
            RMT_CHANNEL_0, 
            GPIO_NUM_13
        ),
        storage,
        REFRESH_RATE_HZ
    );
}
