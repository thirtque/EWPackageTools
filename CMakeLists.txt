cmake_minimum_required(VERSION 3.20)
project(EWPackageTools)

set(CMAKE_CXX_STANDARD 20)

include(cmake/Variables.cmake)
include(cmake/build/ImGui.cmake)
include(cmake/build/LodePng.cmake)
include(cmake/Dependencies.cmake)

add_executable(EWPackageTools src/buffer.cpp src/hmg.cpp src/image.cpp src/package.cpp src/dialog.cpp src/ui.cpp src/main.cpp)
target_include_directories(EWPackageTools PRIVATE include)
target_link_libraries(EWPackageTools PRIVATE ${DEPENDENCIES})

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
