//
// Created by Thomas Vallentin on 01/04/2022.
//

#include "Widget.h"
#include "Logging.h"

#include <imgui.h>

namespace Rebound {

    void Widget::OnImGuiRender() {
        if (m_visibility) {
            PreRender();
            ImGui::Begin(m_title.c_str(), &m_visibility);

            Render();

            ImGui::End();
            PostRender();
        }
    }

}
