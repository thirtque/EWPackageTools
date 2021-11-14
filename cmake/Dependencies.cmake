set(DEPENDENCIES_DIR "${PROJECT_SOURCE_DIR}/libs")

# opengl
find_package(OpenGL REQUIRED)

# glfw (https://www.glfw.org/docs/latest/compile_guide.html)
list(APPEND DEPENDENCIES glfw)
set(GLFW_DIR ${DEPENDENCIES_DIR}/glfw)

#set(GLFW_LIBRARY_TYPE STATIC) # set by default?
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})

# imgui
list(APPEND DEPENDENCIES imgui)
set(IMGUI_DIR ${DEPENDENCIES_DIR}/imgui)

add_library(imgui STATIC)

target_sources(imgui
        PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp

        PRIVATE
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        )

target_include_directories(imgui
        PUBLIC ${IMGUI_DIR}
        PUBLIC ${IMGUI_DIR}/backends
        )

target_link_libraries(imgui PRIVATE ${OPENGL_LIBRARIES} glfw)

# nativefiledialog (https://github.com/btzy/nativefiledialog-extended#cmake-projects)
list(APPEND DEPENDENCIES nfd)
add_subdirectory(${DEPENDENCIES_DIR}/nativefiledialog-extended)

# zstd (https://github.com/facebook/zstd/tree/dev/build/cmake)
list(APPEND DEPENDENCIES libzstd_static)
set(ZSTD_DIR ${DEPENDENCIES_DIR}/zstd)
set(ZSTD_BUILD_PROGRAMS OFF CACHE BOOL "" FORCE)
set(ZSTD_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(ZSTD_BUILD_SHARED OFF CACHE BOOL "" FORCE)
include_directories(SYSTEM ${ZSTD_DIR}/lib)
add_subdirectory(${ZSTD_DIR}/build/cmake)

# fmt (https://fmt.dev/latest/usage.html#usage-with-cmake)
list(APPEND DEPENDENCIES fmt::fmt)
add_subdirectory(${DEPENDENCIES_DIR}/fmt)

