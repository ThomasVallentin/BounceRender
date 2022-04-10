//
// Created by Thomas Vallentin on 01/04/2022.
//

#include "SceneHierarchy.h"

#include "Rebound/Scene/Entity.h"

#include "imgui.h"
#include "Rebound/Core/Logging.h"
#include "Rebound/Core/Inputs.h"
#include "imgui_internal.h"


namespace Rebound {

    void SceneHierarchyWidget::SetScene(const std::shared_ptr<Scene> &scene) {
        m_scene = scene;
    }

    void SceneHierarchyWidget::PreRender() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(1.0f, 5.0f));
    }

    void SceneHierarchyWidget::Render() {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 2.0f));

        for (const auto &root : m_scene->GetRootEntities()) {
            RecurseEntity(root);
        }

        ImGui::PopStyleVar();
    }

    void SceneHierarchyWidget::PostRender() {
        ImGui::PopStyleVar();
    }

    void SceneHierarchyWidget::RecurseEntity(const Entity& entity) {
        const uint32_t childCount = entity.GetChildCount();
        ImGuiTreeNodeFlags nodeFlags = (ImGuiTreeNodeFlags_FramePadding |
                                        ImGuiTreeNodeFlags_OpenOnArrow |
                                        ImGuiTreeNodeFlags_SpanAvailWidth);

        if (!childCount) {
            nodeFlags |= ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
        }

        if (IsSelected(entity)) {
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        bool opened = ImGui::TreeNodeEx((void*)(intptr_t)entity.GetHandle(),
                                        nodeFlags,
                                        entity.GetName().c_str());

        // Item is clicked without toggling it, add it to the selection
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
            if (Input::IsKeyPressed(KeyCode::Left_shift))
                SelectEntity(entity);

            else if (Input::IsKeyPressed(KeyCode::Left_control))
                DeselectEntity(entity);

            else {
                ClearSelection();
                SelectEntity(entity);
            }
        }

        if (opened) {
            for (size_t i = 0; i < childCount; i++) {
                RecurseEntity(entity.GetChild(i));
            }
        }


        if (opened && childCount) {
            ImGui::TreePop();
        }
    }

}
