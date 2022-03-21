//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "App/Core/Application.h"

#include "UILayer.h"

#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Bounce::Gui {

    void UILayer::OnAttach() {
    }

    void UILayer::OnImGuiRender() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void UILayer::OnDetach() {
    }

}