# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.10.5)

project(colproc)

add_library(${PROJECT_NAME})

# Core
target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    "include"
)

target_sources(
    ${PROJECT_NAME} PUBLIC
    src/core/util/util.cpp
    src/core/canvas/canvas_console.cpp
    src/core/canvas/canvas.cpp
)



# Lua related stuff
include("CPM.cmake")

add_subdirectory(src/lua)
target_link_libraries(${PROJECT_NAME} liblua)

CPMAddPackage("gh:vinniefalco/LuaBridge#2.6")
target_link_libraries(${PROJECT_NAME} LuaBridge)
