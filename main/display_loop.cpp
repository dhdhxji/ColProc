#include "display_loop.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "colproc/canvas/canvas.h"


struct display_loop_ctx
{
    ColProc* proc;
    Canvas* canvas;
};

extern "C" {
    static void display_timer_cb(TimerHandle_t t);    
}

static void display_timer_cb(TimerHandle_t t) {
    display_loop_ctx* ctx = (display_loop_ctx*)pvTimerGetTimerID(t);
    uint32_t time = esp_timer_get_time() / 1000;

    ctx->proc->get_colors(time, ctx->canvas);
    ctx->canvas->display();
}

void display_loop_start(
    ColProc* processor, 
    Canvas* canvas,
    uint32_t refresh_rate 
) {
    display_loop_ctx* ctx = new display_loop_ctx();
    ctx->proc = processor;
    ctx->canvas = canvas;

    uint32_t period_freertos_ticks = (1000/(refresh_rate*portTICK_PERIOD_MS));

    TimerHandle_t tim = xTimerCreate(
        "LED", 
        period_freertos_ticks, 
        pdTRUE, 
        ctx, 
        display_timer_cb
    );
    xTimerStart(tim, portMAX_DELAY);
}