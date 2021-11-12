cmake_minimum_required(VERSION 3.20)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libs)

add_executable(untitled3)

target_sources(untitled3 PRIVATE main.cpp)

target_link_libraries(untitled3 PRIVATE glfw imgui fmt::fmt)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
