#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <fmt/core.h>
#include <vector>
#include <fstream>
#include <array>
#include "dialog.h"

struct State {
    GLFWwindow *glfwWindow;
};

bool InitializeGlfw(State &state) {

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    state.glfwWindow = glfwCreateWindow(1280, 720, "EWPackageTools", nullptr, nullptr);
    if (!state.glfwWindow) {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(state.glfwWindow);

    return true;
}

struct ImVec4 HexToVec4(int hex) {
    return ImVec4{
            (float) (hex >> 16 & 0xFF) / 255.0f,
            (float) (hex >> 8 & 0xFF) / 255.0f,
            (float) (hex & 0xFF) / 255.0f,
            1.0
    };
}

void InitializeImGuiStyle() {
    ImGuiStyle &style = ImGui::GetStyle();

    // Padding
    style.WindowPadding = ImVec2(4.00f, 4.00f);
    style.FramePadding = ImVec2(8.00f, 8.00f);
    style.CellPadding = ImVec2(8.00f, 8.00f);
    //style.TouchExtraPadding = ImVec2(16.00f, 16.00f);
    //style.DisplayWindowPadding = ImVec2(16.00f, 16.00f);
    //style.DisplaySafeAreaPadding = ImVec2(16.00f, 16.00f);

    // Spacing
    style.ItemSpacing = ImVec2(16.00f, 16.00f);
    style.ItemInnerSpacing = ImVec2(8.00f, 8.00f);

    // Rounding
    style.WindowRounding = 1;
    style.ChildRounding = 1;
    style.PopupRounding = 1;
    style.FrameRounding = 1;
    style.ScrollbarRounding = 1;
    style.GrabRounding = 1;
    style.TabRounding = 1;

    // Border
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 0;
    style.PopupBorderSize = 0;
    style.FrameBorderSize = 0;
    style.TabBorderSize = 0;

    //style.IndentSpacing = 0;
    //style.ScrollbarSize = 0;
    //style.GrabMinSize = 0;
    //style.GrabRounding = 0;
    //style.LogSliderDeadzone = 0;

    ImGui::PushStyleColor(ImGuiCol_Button, HexToVec4(0x0f62fe));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HexToVec4(0x0353e9));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, HexToVec4(0x002d9c));

    style.Colors[ImGuiCol_Text] = HexToVec4(0xffffff);
    //style.Colors[ImGuiCol_TextDisabled] = ImVec4{1.0, 0.0, 1.0, 0.0}ImVec4{1.0, 0.0, 1.0, 0.0};
    style.Colors[ImGuiCol_WindowBg] = HexToVec4(0x262626);
    style.Colors[ImGuiCol_ChildBg] = HexToVec4(0x262626);
    //style.Colors[ImGuiCol_PopupBg] = ImVec4{1.0, 0.0, 1.0, 0.0}ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_Border] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_BorderShadow] = ImVec4{1.0, 0.0, 1.0, 0.0};
    style.Colors[ImGuiCol_FrameBg] = HexToVec4(0x393939);
    style.Colors[ImGuiCol_FrameBgHovered] = HexToVec4(0x4c4c4c);
    style.Colors[ImGuiCol_FrameBgActive] = HexToVec4(0x6f6f6f);
    style.Colors[ImGuiCol_TitleBg] = HexToVec4(0x161616);
    style.Colors[ImGuiCol_TitleBgActive] = HexToVec4(0x0f62fe);
    style.Colors[ImGuiCol_TitleBgCollapsed] = HexToVec4(0x161616);
    //style.Colors[ImGuiCol_MenuBarBg] = ImVec4{1.0, 0.0, 1.0, 1.0};
    style.Colors[ImGuiCol_ScrollbarBg] = HexToVec4(0x161616);
    style.Colors[ImGuiCol_ScrollbarGrab] = HexToVec4(0x525252);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = HexToVec4(0x0353e9);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = HexToVec4(0x002d9c);
    style.Colors[ImGuiCol_CheckMark] = HexToVec4(0xffffff);
    style.Colors[ImGuiCol_SliderGrab] = HexToVec4(0xffffff);
    style.Colors[ImGuiCol_SliderGrabActive] = HexToVec4(0x4589ff);
    style.Colors[ImGuiCol_Button] = HexToVec4(0x393939);
    style.Colors[ImGuiCol_ButtonHovered] = HexToVec4(0x656565);
    style.Colors[ImGuiCol_ButtonActive] = HexToVec4(0x6f6f6f);
    //style.Colors[ImGuiCol_Header] = ImVec4{1.0, 0.0, 1.0, 0.0};
    style.Colors[ImGuiCol_HeaderHovered] = HexToVec4(0x4c4c4c);
    //style.Colors[ImGuiCol_HeaderActive] = ImVec4{1.0, 0.0, 1.0, 0.0};
    style.Colors[ImGuiCol_Separator] = HexToVec4(0x161616);
    style.Colors[ImGuiCol_SeparatorHovered] = HexToVec4(0x0353e9);
    style.Colors[ImGuiCol_SeparatorActive] = HexToVec4(0x002d9c);
    //style.Colors[ImGuiCol_ResizeGrip] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_ResizeGripActive] = ImVec4{1.0, 0.0, 1.0, 0.0};
    style.Colors[ImGuiCol_Tab] = HexToVec4(0x525252);
    style.Colors[ImGuiCol_TabHovered] = HexToVec4(0x4c4c4c);
    style.Colors[ImGuiCol_TabActive] = HexToVec4(0x393939);
    style.Colors[ImGuiCol_TabUnfocused] = HexToVec4(0x525252);
    style.Colors[ImGuiCol_TabUnfocusedActive] = HexToVec4(0x393939);
    style.Colors[ImGuiCol_DockingPreview] = HexToVec4(0x0f62fe);
    //style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_PlotLines] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_PlotHistogram] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_TableHeaderBg] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_TableBorderStrong] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_TableBorderLight] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_TableRowBg] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_TextSelectedBg] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_DragDropTarget] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_NavHighlight] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4{1.0, 0.0, 1.0, 0.0};
    //style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4{1.0, 0.0, 1.0, 0.0}
}

void InitializeImGuiFonts() {
    ImGuiIO &io = ImGui::GetIO();

    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;
    iconsConfig.GlyphMinAdvanceX = 24;
    iconsConfig.GlyphMaxAdvanceX = 24;
    iconsConfig.GlyphOffset = ImVec2(0, 3);

    static const ImWchar iconsGlyphRanges[] = {0xea02, 0xef56, 0};

    io.Fonts->AddFontFromFileTTF("resources/roboto.ttf", 20);
    io.Fonts->AddFontFromFileTTF("resources/tabler-icons.ttf", 24, &iconsConfig, iconsGlyphRanges);
}

void InitializeImGui(State &state) {
    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    InitializeImGuiFonts();
    InitializeImGuiStyle();

    ImGui_ImplGlfw_InitForOpenGL(state.glfwWindow, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

bool Initialize(State &state) {
    if (!InitializeGlfw(state)) {
        return false;
    }
    InitializeImGui(state);
    InitializeDialog();

    return true;
}

bool Loop(State &state) {
    return glfwWindowShouldClose(state.glfwWindow) == 0;
}

void FrameStart(State &state) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

struct Entry {
    std::string Name;
    bool Opened;
};

std::vector<Entry> entries;

struct PackageHeaderData {
    uint32_t Signature;
    uint32_t EntryCount;
};

struct PackageEntryData {
    std::string Name;
    uint32_t Position;
    uint32_t Compression;
    uint32_t UncompressedLength;
    uint32_t Length;
};

uint32_t BufferReadUint32(const uint8_t *buffer) {
    return buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
};

// @todo Implement read error handling
PackageHeaderData ReadPackageHeader(std::ifstream &packageFile) {
    std::array<uint8_t, 8> buffer{};
    packageFile.read(reinterpret_cast<char *>(buffer.data()), buffer.size());

    uint32_t packageHeader = BufferReadUint32(buffer.data());
    uint32_t packageEntryCount = BufferReadUint32(buffer.data() + 4);

    return {packageHeader, packageEntryCount};
}

// Buffer size assumes maximum entry name length of 240 characters
const auto packageEntryBufferSize = 256;
const auto packageEntryInformationSize = 16;

// @todo Implement read error handling
PackageEntryData ReadPackageEntry(std::ifstream &packageFile) {
    std::array<uint8_t, packageEntryBufferSize> buffer{};

    for (auto b = 0, p = 0; b < packageEntryBufferSize; b += packageEntryInformationSize) {
        packageFile.read(reinterpret_cast<char *>(buffer.data() + b), packageEntryInformationSize);

        for (auto bo = 0; bo < packageEntryInformationSize; bo++, p++) {
            // Find null terminator in entry name
            if (buffer[p] != 0) {
                continue;
            }

            // Read missing bytes for entry information
            packageFile.read(reinterpret_cast<char *>(buffer.data() + b + packageEntryInformationSize), bo + 1);

            // Deserialize entry name
            std::string entryName(reinterpret_cast<const char *>(buffer.data()), p);

            // Skip null terminator
            p++;

            // Deserialize entry information
            uint32_t offset = BufferReadUint32(buffer.data() + p);
            uint32_t compression = BufferReadUint32(buffer.data() + p + 4);
            uint32_t uncompressedLength = BufferReadUint32(buffer.data() + p + 8);
            uint32_t length = BufferReadUint32(buffer.data() + p + 12);

            return {entryName, offset, compression, uncompressedLength, length};
        }
    }
}

void OpenPackage() {
    auto fileDialogResult = OpenFileDialog();
    if (!fileDialogResult.Status) {
        return;
    }

    std::ifstream packageFile;
    packageFile.open(fileDialogResult.Path, std::ifstream::binary);
    if (packageFile) {
        PackageHeaderData packageHeader = ReadPackageHeader(packageFile);

        if (packageHeader.Signature != 0x6A37) {
            return;
        }

        entries.clear();
        for (uint32_t i = 0; i < packageHeader.EntryCount; i++) {
            PackageEntryData packageEntry = ReadPackageEntry(packageFile);
            entries.push_back({packageEntry.Name});
        }
    }
    packageFile.close();
}

void RenderToolBar() {
    ImGui::Button("\ueb62 Save");

    ImGui::SameLine();
    if (ImGui::Button("\ueaad Open")) {
        OpenPackage();
    }
}

void RenderEntryList() {
    ImGui::Begin("Entries##EntryList");
    for (Entry &e: entries) {
        if (ImGui::Selectable(e.Name.c_str(), e.Opened)) {
            e.Opened = true;
        }
    }
    ImGui::End();
}

void RenderEntryPreview() {
    ImGui::Begin("Preview##EntryPreview");
    bool anyEntryOpened = std::any_of(entries.begin(), entries.end(), [](Entry &e) {
        return e.Opened;
    });
    if (anyEntryOpened) {
        ImGuiTabBarFlags tabsFlags = ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyScroll;
        if (ImGui::BeginTabBar("##EntryPreviewTabs", tabsFlags)) {
            for (Entry &e: entries) {
                if (e.Opened && ImGui::BeginTabItem(e.Name.c_str(), &e.Opened, ImGuiTabItemFlags_None)) {
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }
    } else {
        auto windowSize = ImGui::GetWindowSize();
        if (entries.empty()) {
            auto message = "\ueaff Open a package to start!";
            auto messageSize = ImGui::CalcTextSize(message);
            auto buttonSize = ImVec2{200, ImGui::GetFrameHeight()};

            ImGui::SetCursorPos(ImVec2{
                    (windowSize.x - messageSize.x) / 2,
                    (windowSize.y - (messageSize.y + buttonSize.y)) / 2
            });
            ImGui::Text(message);

            ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2);
            ImGui::PushStyleColor(ImGuiCol_Button, HexToVec4(0x0f62fe));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HexToVec4(0x0353e9));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, HexToVec4(0x002d9c));
            if (ImGui::Button("Open package", buttonSize)) {
                OpenPackage();
            }
            ImGui::PopStyleColor(3);
        } else {
            const char *message = "\uebbc Select any of the entries to start!";
            auto messageSize = ImGui::CalcTextSize(message);

            ImGui::SetCursorPos(ImVec2{
                    (windowSize.x - messageSize.x) / 2,
                    (windowSize.y - messageSize.y) / 2
            });
            ImGui::Text(message);
        }
    }
    ImGui::End();
}

void RenderMain() {
    ImGuiViewport *viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                            ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                            ImGuiWindowFlags_NoNavFocus;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("##DockSpaceWindow", nullptr, dockSpaceWindowFlags);
    ImGui::PopStyleVar(3);

    ImGuiID dockSpaceId = ImGui::GetID("##DockSpace");
    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), 0, nullptr);

    ImGuiWindowFlags toolBarWindowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar |
                                          ImGuiWindowFlags_NoSavedSettings;
    float toolBarHeight = ImGui::GetFrameHeight() + 8 * 2;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
    ImGui::BeginViewportSideBar("##ToolBarWindow", viewport, ImGuiDir_Up, toolBarHeight, toolBarWindowFlags);
    ImGui::PopStyleVar(3);

    RenderToolBar();

    ImGui::End();

    ImGui::End();

    static bool dockSpaceInitialized = false;
    if (!dockSpaceInitialized) {
        dockSpaceInitialized = true;

        ImGui::DockBuilderRemoveNode(dockSpaceId);
        ImGui::DockBuilderAddNode(dockSpaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockSpaceId, viewport->Size);

        ImGuiID dockMainId = dockSpaceId;
        ImGuiID dockLeftId = ImGui::DockBuilderSplitNode(dockMainId, ImGuiDir_Left, 0.3f, nullptr, &dockMainId);

        ImGui::DockBuilderDockWindow("Entries##EntryList", dockLeftId);
        ImGui::DockBuilderDockWindow("Preview##EntryPreview", dockMainId);

        ImGui::DockBuilderFinish(dockSpaceId);
    }

    RenderEntryList();
    RenderEntryPreview();
}

void FrameEnd(State &state) {
    ImGui::Render();

    int w, h;
    glfwGetFramebufferSize(state.glfwWindow, &w, &h);
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(state.glfwWindow);
}

void Finalize() {
    FinalizeDialog();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwTerminate();
}

int main() {
    State state{};
    Initialize(state);
    while (Loop(state)) {
        FrameStart(state);
        RenderMain();
        FrameEnd(state);
    }
    Finalize();

    return 0;
}
