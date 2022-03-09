# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.10.5)

project(colproc)

add_library(${PROJECT_NAME})

# Core
target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    "include"
    ${CMAKE_CURRENT_BINARY_DIR}
)

#target_include_directories(
#    ${PROJECT_NAME} PUBLIC
#)

target_sources(
    ${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/util/util.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/canvas/canvas.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/runtime/runtime.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/runtime/lua_runtime.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/runtime/map_var_storage.cpp"
)



# Lua related stuff
include("CPM.cmake")

add_subdirectory(src/lua)
target_link_libraries(${PROJECT_NAME} liblua)

CPMAddPackage("gh:vinniefalco/LuaBridge#2.6")
target_link_libraries(${PROJECT_NAME} LuaBridge)

add_subdirectory("src/mcufont")
target_link_libraries(colproc mcufont)



file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/colproc")

# Code generation for lua bindings
add_custom_command(
    OUTPUT "colproc/classes.json"
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/util/class_parser.py
        -i "${CMAKE_CURRENT_SOURCE_DIR}/include/colproc/"
        -o "colproc/classes.json"
        --include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        --root_class "ColRGB" "Canvas" "Variable<T>" "ColProc" 
    DEPENDS "include" "util/class_parser.py"
    VERBATIM 
)

add_custom_target(classes DEPENDS "colproc/classes.json")



set(CODEGEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/colproc)
set(BINDIGS_DIR ${CODEGEN_DIR}/lua)

add_custom_command(
    OUTPUT "${BINDIGS_DIR}/bindings.h"
    COMMAND cog 
        -D builder_fn_name=colproc 
        -D class_meta_path=colproc/classes.json 
        -o "${BINDIGS_DIR}/bindings.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lua/bindings.cog"
    DEPENDS classes "${CMAKE_CURRENT_SOURCE_DIR}/src/lua/bindings.cog"
    VERBATIM
)

add_custom_target(
    lua_bindings DEPENDS 
    classes
    "${BINDIGS_DIR}/bindings.h"
    "${CMAKE_CURRENT_BINARY_DIR}/colproc/classes.json"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lua/bindings.cog"
)
add_dependencies(${PROJECT_NAME} lua_bindings)