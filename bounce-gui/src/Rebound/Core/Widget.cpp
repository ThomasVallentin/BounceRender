//
// Created by Thomas Vallentin on 01/04/2022.
//

#include "Widget.h"
#include "Logging.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Rebound {

    void Widget::OnImGuiRender() {
        if (m_visibility) {
            PreRender();

            ImGui::Begin(m_title.c_str(), &m_visibility, m_flags | ImGuiWindowFlags_NoCollapse);

            // Remove the Window menu button if it is docked
            if(ImGuiDockNode* Node = ImGui::GetWindowDockNode())
                Node->LocalFlags |= ImGuiDockNodeFlags_NoWindowMenuButton;

            Render();

            ImGui::End();
            PostRender();
        }
    }

}
