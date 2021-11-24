#include "ui.h"

namespace Ui {
    bool Initialize(State &state) {
        if (!InitializeGlfw(state)) {
            return false;
        }
        InitializeImGui(state);
        Dialog::Initialize();

        return true;
    }

    bool InitializeGlfw(State &state) {
        if (!glfwInit()) {
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

        state.glfwWindow = glfwCreateWindow(1280, 720, "EWPackageTools", nullptr, nullptr);
        if (!state.glfwWindow) {
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(state.glfwWindow);

        return true;
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

    ImVec4 HexToVec4(const int hex) {
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

    ImFont *fontSansSerifMedium;
    ImFont *fontMonospaceMedium;

    // @todo Implement better font managing
    void InitializeImGuiFonts() {
        ImGuiIO &io = ImGui::GetIO();

        ImFontConfig iconsMediumConfig;
        iconsMediumConfig.MergeMode = true;
        iconsMediumConfig.GlyphMinAdvanceX = 22;
        iconsMediumConfig.GlyphMaxAdvanceX = 22;
        iconsMediumConfig.GlyphOffset = ImVec2(0, 2);

        static const ImWchar iconsGlyphRanges[] = {0xea02, 0xef7a, 0};

        fontSansSerifMedium = io.Fonts->AddFontFromFileTTF("resources/roboto.ttf", 18);
        io.Fonts->AddFontFromFileTTF("resources/tabler-icons.ttf", 22, &iconsMediumConfig, iconsGlyphRanges);

        fontMonospaceMedium = io.Fonts->AddFontFromFileTTF("resources/fira-code.ttf", 18);
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
        Dialog::Finalize();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext();

        glfwTerminate();
    }

    Package::Package package;

    void OpenPackage() {
        auto fileDialogResult = Dialog::OpenFile();
        if (!fileDialogResult.Status) {
            return;
        }

        std::ifstream packageFile;
        packageFile.open(fileDialogResult.Path, std::ifstream::binary);
        if (packageFile) {
            package = Package::ReadPackage(packageFile);
        }
        packageFile.close();
    }

    void ExtractEntry(const Package::Entry &entry) {
        auto fileDialogResult = Dialog::SaveFile(entry.Information.Name);
        if (!fileDialogResult.Status) {
            return;
        }

        std::ofstream entryFile;
        entryFile.open(fileDialogResult.Path, std::ifstream::binary | std::ifstream::trunc);
        WriteEntry(entryFile, entry);
        entryFile.close();
    }

    void ExtractHmgEntryAsPng(const Package::Entry &entry) {
        auto fileName = entry.Information.Name + ".png";
        std::replace(fileName.begin(), fileName.end(), '/', '_');
        std::replace(fileName.begin(), fileName.end(), '\\', '_');

        auto fileDialogResult = Dialog::SaveFile(fileName);
        if (!fileDialogResult.Status) {
            return;
        }

        auto imageData = new std::vector<uint8_t>();
        uint32_t imageWidth;
        uint32_t imageHeight;

        Hmg::Decode(*entry.Data, *imageData, imageWidth, imageHeight);

        auto pngData = new std::vector<uint8_t>();

        lodepng::encode(*pngData, *imageData, imageWidth, imageHeight);

        std::ofstream entryFile;
        entryFile.open(fileDialogResult.Path, std::ifstream::binary | std::ifstream::trunc);
        entryFile.write(reinterpret_cast<char *>(pngData->data()), pngData->size());
        entryFile.close();

        delete imageData;
        delete pngData;
    }

    std::string GetEntryTypeIcon(Package::EntryType type) {
        if (type == Package::EntryType::ImagePng || type == Package::EntryType::ImageHmg) {
            return "\ueb0a";
        }
        if (type == Package::EntryType::Text) {
            return "\uea77";
        }
        if (type == Package::EntryType::Binary) {
            return "\uee08";
        }
        return "\uec9d";
    }

    void RenderToolBar() {
        if (ImGui::Button("\ueaad Open")) {
            OpenPackage();
        }
    }

    void RenderEntryList() {
        ImGui::Begin("Entries##EntryList");

        for (auto &e: package.Entries) {
            if (ImGui::Selectable(fmt::format("{} {}", GetEntryTypeIcon(e.Type), e.Information.Name).c_str(),
                    e.Opened)) {
                e.Opened = true;
                e.Selected = true;
            }
        }

        ImGui::End();
    }

    void RenderEntryPreviewNoPackage() {
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const char *message = "\ueaff Open a package to start!";
        const ImVec2 messageSize = ImGui::CalcTextSize(message);
        const ImVec2 buttonSize = ImVec2{200, ImGui::GetFrameHeight()};

        ImGui::SetCursorPos(ImVec2{
                (windowSize.x - messageSize.x) / 2,
                (windowSize.y - (messageSize.y + buttonSize.y)) / 2
        });
        ImGui::Text("%s", message);

        ImGui::SetCursorPosX((windowSize.x - buttonSize.x) / 2);
        ImGui::PushStyleColor(ImGuiCol_Button, HexToVec4(0x0f62fe));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HexToVec4(0x0353e9));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, HexToVec4(0x002d9c));
        if (ImGui::Button("Open package", buttonSize)) {
            OpenPackage();
        }
        ImGui::PopStyleColor(3);
    }

    void RenderEntryPreviewNoEntry() {
        const ImVec2 windowSize = ImGui::GetWindowSize();

        const char *message = "\uebbc Select any of the entries to start!";
        const ImVec2 messageSize = ImGui::CalcTextSize(message);

        ImGui::SetCursorPos(ImVec2{
                (windowSize.x - messageSize.x) / 2,
                (windowSize.y - messageSize.y) / 2
        });
        ImGui::Text("%s", message);
    }

    void RenderEntryPreviewText(std::vector<uint8_t> *entryData) {
        ImGui::PushFont(fontMonospaceMedium);

        const ImVec2 inputTextSize = ImGui::GetContentRegionAvail();

        std::string entryDataString(entryData->begin(), entryData->end());
        ImGui::InputTextMultiline("##EntryDataPreviewText", &entryDataString, inputTextSize,
                ImGuiInputTextFlags_ReadOnly,
                nullptr);

        ImGui::PopFont();
    }

    void RenderEntryPreviewImage(Image::Texture texture) {
        ImGui::Image(
                reinterpret_cast<ImTextureID>(texture.Id),
                ImVec2{
                        static_cast<float>(texture.Width),
                        static_cast<float>(texture.Height)
                }
        );
    }

    void RenderEntryPreviewHex(std::vector<uint8_t> *entryData) {
        const int cellsPerRow = 16;

        const float charWidth = ImGui::CalcTextSize("F").x;
        const float charHeight = ImGui::GetTextLineHeight();

        const float padding = 8.0f;

        const float addressX = 0.0f;
        const float addressWidth = charWidth * 5 + padding;

        const float hexX = addressX + addressWidth + padding;
        const float hexCellWidth = charWidth * 2 + padding;
        const float hexWidth = hexCellWidth * cellsPerRow - padding;

        const float borderX = hexX + hexWidth + padding;

        const float asciiX = borderX + padding;
        const float asciiCellWidth = charWidth;

        ImDrawList *windowDrawList = ImGui::GetWindowDrawList();

        const float clipperRowHeight = charHeight;
        const int clipperRowCount = entryData->size() / cellsPerRow + 1;

        ImGui::PushFont(fontMonospaceMedium);

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        const ImVec2 windowPosition = ImGui::GetWindowPos();

        windowDrawList->AddLine(
                ImVec2(windowPosition.x + borderX, windowPosition.y),
                ImVec2(windowPosition.x + borderX, windowPosition.y + clipperRowHeight * clipperRowCount),
                ImGui::GetColorU32(ImGuiCol_Border)
        );

        ImGuiListClipper clipper;
        clipper.Begin(clipperRowCount, clipperRowHeight);
        while (clipper.Step()) {
            for (int r = clipper.DisplayStart; r < clipper.DisplayEnd; r++) {
                int address = r * cellsPerRow;

                ImGui::Text("%04x:", address);

                for (uint8_t o = 0; o < cellsPerRow && address + o < entryData->size(); o++) {
                    ImGui::SameLine(hexX + hexCellWidth * o);

                    uint8_t d = (*entryData)[address + o];
                    if (d == 0) {
                        ImGui::TextDisabled("00");
                    } else {
                        ImGui::Text("%02x", d);
                    }
                }

                for (uint8_t o = 0; o < cellsPerRow && address + o < entryData->size(); o++) {
                    ImGui::SameLine(asciiX + asciiCellWidth * o);

                    uint8_t d = (*entryData)[address + o];
                    if (std::isprint(static_cast<unsigned char>(d))) {
                        ImGui::Text("%c", d);
                    } else {
                        if (d == 0) {
                            ImGui::TextDisabled(".");
                        } else {
                            ImGui::Text(".");
                        }
                    }
                }
            }
        }

        ImGui::PopStyleVar(2);

        ImGui::PopFont();
    }

    void RenderEntryPreview() {
        ImGui::Begin("Preview##EntryPreview");
        bool anyEntryOpened = std::ranges::any_of(package.Entries, [](Package::Entry &e) {
            return e.Opened;
        });
        if (anyEntryOpened) {
            ImGuiTabBarFlags tabsFlags = ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyScroll;
            if (ImGui::BeginTabBar("##EntryPreviewTabs", tabsFlags)) {
                for (auto &e: package.Entries) {
                    ImGuiTabItemFlags tabItemFlags = ImGuiTabItemFlags_None;
                    if (e.Selected) {
                        tabItemFlags |= ImGuiTabItemFlags_SetSelected;
                        e.Selected = false;
                    }
                    if (e.Opened &&
                            ImGui::BeginTabItem(
                                    fmt::format("{} {}", GetEntryTypeIcon(e.Type), e.Information.Name).c_str(),
                                    &e.Opened, tabItemFlags)) {
                        if (ImGui::Button("\uede9 Extract")) {
                            ExtractEntry(e);
                        }

                        if (e.Type == Package::EntryType::ImageHmg) {
                            ImGui::SameLine();
                            if (ImGui::Button("\uede9 Extract as PNG")) {
                                ExtractHmgEntryAsPng(e);
                            }
                        }

                        const ImVec2 tabItemContentSize = ImGui::GetContentRegionAvail();

                        ImGui::BeginChild("##EntryDataPreview", tabItemContentSize, false,
                                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav);

                        if (e.Type == Package::EntryType::Text) {
                            RenderEntryPreviewText(e.Data);
                        } else if (e.Type == Package::EntryType::ImageHmg) {
                            // @todo Implement better autoloading
                            if (e.Texture.Id == 0) {
                                e.Texture = Image::CreateTextureFromHmg(*e.Data);
                            }

                            RenderEntryPreviewImage(e.Texture);
                        } else if (e.Type == Package::EntryType::ImagePng) {
                            // @todo Implement better autoloading
                            if (e.Texture.Id == 0) {
                                e.Texture = Image::CreateTextureFromPng(*e.Data);
                            }

                            RenderEntryPreviewImage(e.Texture);
                        } else {
                            RenderEntryPreviewHex(e.Data);
                        }

                        ImGui::EndChild();

                        ImGui::EndTabItem();
                    }
                }
                ImGui::EndTabBar();
            }
        } else {
            if (package.Entries.empty()) {
                RenderEntryPreviewNoPackage();
            } else {
                RenderEntryPreviewNoEntry();
            }
        }
        ImGui::End();
    }

    void RenderFrame() {
        ImGuiViewport *viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        const ImGuiWindowFlags dockSpaceWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
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

        const ImGuiWindowFlags toolBarWindowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoSavedSettings;
        const float toolBarPadding = 8.0f;
        const float toolBarHeight = ImGui::GetFrameHeight() + toolBarPadding * 2;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(toolBarPadding, toolBarPadding));
        ImGui::BeginViewportSideBar("##ToolBarWindow", viewport, ImGuiDir_Up, toolBarHeight, toolBarWindowFlags);
        ImGui::PopStyleVar(3);

        RenderToolBar();

        ImGui::End(); // DockSpace

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
}
