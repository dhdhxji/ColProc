idf_component_register(
    SRCS "util.cpp" "canvas/canvas.cpp" "canvas/canvas_console.cpp" "canvas/canvas_strip.cpp"
    INCLUDE_DIRS "include"
    REQUIRES "led_strip" "esp32_mcufont"
)

# Generate ColProc and Variable class description
get_target_property(include_dirs_target ${COMPONENT_LIB} INCLUDE_DIRECTORIES)



add_custom_command(
    OUTPUT colproc/classes.json
    COMMAND python3 ${COMPONENT_DIR}/parse_classes.py
        -i ${COMPONENT_DIR}/include/colproc/
        -o ./colproc/classes.json
        --include_path ${include_dirs_target}
        --root_class "ColRGB" "Canvas" "Variable<T>" "ColProc" 
    DEPENDS ${COMPONENT_DIR}/include/colproc ${COMPONENT_DIR}/parse_classes.py
    VERBATIM 
)

add_custom_target(classes DEPENDS "colproc/classes.json")



add_custom_command(
    OUTPUT colproc/bindings.h
    COMMAND cog 
        -D builder_fn_name=colproc 
        -D class_meta_path=colproc/classes.json 
        -o colproc/bindings.h
        ${COMPONENT_DIR}/bindings.cog
    DEPENDS classes
    VERBATIM
)

add_custom_target(lua_bindings DEPENDS colproc/bindings.h)
add_dependencies(${COMPONENT_LIB} lua_bindings)



set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES "./colproc/classes.json")

set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES colproc/bindings.h)

include("CPM.cmake")



# Add lua build
add_subdirectory(lua)
target_link_libraries(${COMPONENT_LIB} liblua)

# Add LuaBridge
CPMAddPackage("gh:vinniefalco/LuaBridge#2.6")
target_link_libraries(${COMPONENT_LIB} LuaBridge)