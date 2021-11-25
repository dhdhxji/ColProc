#ifndef DISPLAY_LOOP_H
#define DISPLAY_LOOP_H

#include "colproc/colproc.h"
#include "led_strip.h"

void display_loop_start(
    ColProc* processor, 
    led_strip_t* strip,
    size_t led_count,
    uint32_t refresh_rate 
);

#endif // DISPLAY_LOOP_H
