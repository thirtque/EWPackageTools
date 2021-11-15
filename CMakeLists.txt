cmake_minimum_required(VERSION 3.20)
project(EWPackageTools)

set(CMAKE_CXX_STANDARD 20)

include(cmake/Variables.cmake)
include(cmake/build/ImGui.cmake)
include(cmake/Dependencies.cmake)

add_executable(EWPackageTools src/dialog.cpp src/dialog.h)

target_sources(EWPackageTools PRIVATE src/main.cpp)

target_link_libraries(EWPackageTools PRIVATE ${DEPENDENCIES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
