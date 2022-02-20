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


set(CODEGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/colproc)
set(BINDIGS_DIR ${CODEGEN_DIR}/lua)

add_custom_command(
    OUTPUT ${BINDIGS_DIR}/bindings.h
    COMMAND cog 
        -D builder_fn_name=colproc 
        -D class_meta_path=colproc/classes.json 
        -o ${BINDIGS_DIR}/bindings.h
        ${COMPONENT_DIR}/bindings.cog
    DEPENDS classes ${COMPONENT_DIR}/bindings.cog
    VERBATIM
)

add_custom_target(lua_bindings DEPENDS ${BINDIGS_DIR}/bindings.h colproc/classes.json ${COMPONENT_DIR}/bindings.cog)
add_dependencies(${COMPONENT_LIB} lua_bindings)

target_include_directories(${COMPONENT_LIB} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})


set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES "./colproc/classes.json")

set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
    ADDITIONAL_MAKE_CLEAN_FILES ${BINDIGS_DIR}/bindings.h)

include("CPM.cmake")



# Add lua build
add_subdirectory(lua)
target_link_libraries(${COMPONENT_LIB} liblua)

# Add LuaBridge
CPMAddPackage("gh:vinniefalco/LuaBridge#2.6")
target_link_libraries(${COMPONENT_LIB} LuaBridge)