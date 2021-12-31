idf_component_register(
    SRCS "util.cpp" "canvas/canvas.cpp" "canvas/canvas_console.cpp" "canvas/canvas_strip.cpp"
    INCLUDE_DIRS "include"
    REQUIRES "led_strip"
)