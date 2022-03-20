//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "ImGuiLayer.h"

#include "App/Events/MouseEvent.h"
#include "App/Events/KeyEvent.h"
#include "App/Application.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>


namespace Bounce::Gui {

    void ImGuiLayer::OnAttach() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO(); (void) io;
        io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowBorderSize = 1.0f;
        style.ChildBorderSize = 1.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.TabBorderSize = 0.0f;

        style.WindowRounding = 0.0f;
        style.FrameRounding = 1.0f;
        style.TabRounding = 0.0f;
        style.GrabRounding = 2.0f;
        style.ItemSpacing = ImVec2(2, 2);
        style.ItemInnerSpacing = ImVec2(2, 2);

        ImVec4* colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_Text]                   = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
        colors[ImGuiCol_Border]                 = ImVec4(0.26f, 0.26f, 0.26f, 0.50f);
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.42f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.00f, 0.00f, 0.00f, 0.66f);
        colors[ImGuiCol_TitleBg]                = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.22f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.22f, 0.61f, 1.00f, 1.00f);
        colors[ImGuiCol_Button]                 = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
        colors[ImGuiCol_Header]                 = ImVec4(1.00f, 1.00f, 1.00f, 0.16f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(1.00f, 1.00f, 1.00f, 0.24f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
        colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.63f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 0.75f);
        colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
        colors[ImGuiCol_Tab]                    = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);


        io.FontDefault = io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\arial.ttf)", 13);

        // Setup Platform/Renderer backends
        GLFWwindow* window = glfwGetCurrentContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::Begin() {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO &io = ImGui::GetIO();
        Bounce::Gui::Application &app = Bounce::Gui::Application::Get();
        io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(),
                                (float) app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}