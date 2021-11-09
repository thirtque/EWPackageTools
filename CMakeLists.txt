cmake_minimum_required(VERSION 3.20)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs)

add_executable(untitled3)
target_sources(untitled3 PUBLIC main.cpp)
target_link_libraries(untitled3 ${OPENGL_LIBRARIES} glfw imgui)