cmake_minimum_required(VERSION 3.10)

project(lua_simple)

add_executable(app main.cpp)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../../" "${CMAKE_CURRENT_BINARY_DIR}/colproc")
target_link_libraries(app colproc)