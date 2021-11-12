# opengl
find_package(OpenGL REQUIRED)

# glfw (https://www.glfw.org/docs/latest/compile_guide.html)
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw)

#set(GLFW_LIBRARY_TYPE STATIC) # set by default?
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_DIR})

# imgui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

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

# fmt (https://fmt.dev/latest/usage.html#usage-with-cmake)
add_subdirectory(fmt)
