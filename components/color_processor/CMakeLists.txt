idf_component_register(
    SRCS "util.cpp" "canvas/canvas.cpp" "canvas/canvas_console.cpp" "canvas/canvas_strip.cpp"
    INCLUDE_DIRS "include"
    REQUIRES "led_strip" "esp32_mcufont"
)

get_target_property(include_dirs_target ${COMPONENT_LIB} INCLUDE_DIRECTORIES)

add_custom_command(
    OUTPUT colproc/classes.json
    COMMAND python3 ${COMPONENT_DIR}/parse_classes.py -i ${COMPONENT_DIR}/include/colproc/ -o ./colproc/classes.json --include_path ${include_dirs_target}
    DEPENDS ${COMPONENT_DIR}/include/colproc ${COMPONENT_DIR}/parse_classes.py
    VERBATIM 
)

add_custom_target(classes DEPENDS "colproc/classes.json")
add_dependencies(${COMPONENT_LIB} classes)

set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES "./colproc/classes.json")