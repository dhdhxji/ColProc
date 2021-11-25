#include "display_loop.h"
#include "colproc/util/util.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"


struct display_loop_ctx
{
    ColProc* proc;
    led_strip_t* strip;
    size_t led_count;
    color_t* buffer;
};

extern "C" {
    static void display_timer_cb(TimerHandle_t t);    
}

static void display_timer_cb(TimerHandle_t t) {
    display_loop_ctx* ctx = (display_loop_ctx*)pvTimerGetTimerID(t);
    uint32_t time = esp_timer_get_time() / 1000;

    ctx->proc->get_colors(time, ctx->buffer, ctx->led_count);
    ESP_ERROR_CHECK(
        ctx->strip->set_pixels(
            ctx->strip, 
            0,
            ctx->led_count, 
            (const uint8_t*)(ctx->buffer)
        )
    );

    ESP_ERROR_CHECK(ctx->strip->refresh(ctx->strip, 100));
}

void display_loop_start(
    ColProc* processor, 
    led_strip_t* strip,
    size_t led_count,
    uint32_t refresh_rate 
) {
    display_loop_ctx* ctx = new display_loop_ctx();
    ctx->led_count = led_count;
    ctx->proc = processor;
    ctx->strip = strip;
    ctx->buffer = new color_t[led_count];

    uint32_t period_freertos_ticks = (1000 * portTICK_PERIOD_MS)/refresh_rate;

    TimerHandle_t tim = xTimerCreate(
        "LED", 
        period_freertos_ticks, 
        pdTRUE, 
        ctx, 
        display_timer_cb
    );
    xTimerStart(tim, portMAX_DELAY);
}