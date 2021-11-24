#pragma once

#include <fstream>
#include <algorithm>
#include <cstdint>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <fmt/core.h>

#include "image.h"
#include "package.h"
#include "dialog.h"

namespace Ui {
    struct State {
        GLFWwindow *glfwWindow;
    };

    bool Initialize(State &state);

    bool InitializeGlfw(State &state);

    void InitializeImGui(State &state);
    void InitializeImGuiStyle();
    void InitializeImGuiFonts();

    bool Loop(State &state);

    void FrameStart(State &state);
    void RenderFrame();
    void FrameEnd(State &state);

    void Finalize();
}