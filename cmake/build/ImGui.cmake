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

# freetype
set(FREETYPE_DIR ${DEPENDENCIES_DIR}/freetype)
include_directories(SYSTEM ${FREETYPE_DIR}/include)
add_subdirectory(${DEPENDENCIES_DIR}/freetype)

# imgui
set(IMGUI_DIR ${DEPENDENCIES_DIR}/imgui)

add_library(imgui STATIC)

# https://github.com/ocornut/imgui/blob/3fde445b91a357db4d3e78a1526170a479b130f4/imconfig.h#L71-L74
target_compile_definitions(imgui PRIVATE IMGUI_ENABLE_FREETYPE)

target_sources(imgui
        PRIVATE
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/misc/freetype/imgui_freetype.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        )

target_include_directories(imgui
        PUBLIC ${IMGUI_DIR}
        PUBLIC ${IMGUI_DIR}/backends
        PUBLIC ${IMGUI_DIR}/misc/freetype
        )

target_link_libraries(imgui PRIVATE ${OPENGL_LIBRARIES} glfw freetype)
