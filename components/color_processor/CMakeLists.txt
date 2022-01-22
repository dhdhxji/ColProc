idf_component_register(
    SRCS "util.cpp" "canvas/canvas.cpp" "canvas/canvas_console.cpp" "canvas/canvas_strip.cpp"
    INCLUDE_DIRS "include"
    REQUIRES "led_strip" "esp32_mcufont"
)

add_custom_command(
    OUTPUT colproc/classes.json
    COMMAND python3 ${COMPONENT_DIR}/parse_classes.py -i ${COMPONENT_DIR}/colproc/ -o ./colproc/classes.json
    DEPENDS ${COMPONENT_DIR}/include/colproc ${COMPONENT_DIR}/parse_classes.py
    VERBATIM 
)

add_custom_target(classes DEPENDS "colproc/classes.json")
add_dependencies(${COMPONENT_LIB} classes)

set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES "./colproc/classes.json")