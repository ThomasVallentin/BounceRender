//
// Created by Thomas Vallentin on 12/04/2022.
//

#include "AttributeView.h"

#include <glm/glm.hpp>

#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS // Mandatory to be able to subtract ImVec2
#include <imgui_internal.h>


namespace Rebound {

    void IndentedAttributeLabel(const std::string& label, const float& indent) {
        auto labelWidth = ImGui::CalcTextSize(label.c_str()).x;
        ImGui::SetCursorPosX(indent - labelWidth);
        ImGui::Text(label.c_str());
    }

    void ComputeAllBases(const Type& type, std::vector<Type> &result) {
        for (const auto &base: type.GetBases()) {
            if (std::find(result.begin(), result.end(), base) == result.end()) {
                result.push_back(base);
                ComputeAllBases(base, result);
            }
        }
    }

    void AttributeViewWidget::PreRender() {
    }

    void AttributeViewWidget::AddUnsupportedChannel(Entity* entity,
                                                    const std::string &name,
                                                    const AttributeValue &atValue) const {
        ImGui::AlignTextToFramePadding();
        IndentedAttributeLabel(name, m_textValueSplit);
        ImGui::SameLine(0.0f, m_textValueSpacing);

        ImGui::Text("Value of type \"%s\"", atValue.GetTypeName().c_str());
    }

    void AttributeViewWidget::AddVec3Channel(Entity* entity,
                                             const std::string &name,
                                             AttributeValue &atValue) {

        ImGui::AlignTextToFramePadding();
        IndentedAttributeLabel(name, m_textValueSplit);
        ImGui::SameLine(0.0f, m_textValueSpacing);

        glm::vec3 value;
        atValue.As<glm::vec3>(value);
        auto *_value = new float[3]{value.x, value.y, value.z};

        ImGui::PushItemWidth(-FLT_MIN);  // Force the dragFloats to take the whole space available
        if (ImGui::DragFloat3(name.c_str(), _value, 0.1f,
                              -FLT_MAX, FLT_MAX, "%.3f")) {
            value = {_value[0], _value[1], _value[2]};
            entity->SetAttribute(name, value);
        }

    }

    void AttributeViewWidget::Render() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Options")) {
                ImGui::MenuItem("Show unsupported attributes",
                                nullptr,
                                &m_showUnsupportedAttributes);

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (!m_entity) {
            std::string message = "Select an Entity to edit its attributes !";
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 textSize = ImGui::CalcTextSize(message.c_str());

            ImGui::SetCursorPos((windowSize - textSize) * 0.5f);
            ImGui::Text(message.c_str());
            return;
        }

        // Name field
        IndentedAttributeLabel("Name", m_textValueSplit);
        ImGui::SameLine(0.0f, m_textValueSpacing);
        ImGui::Text(m_entity->GetName().c_str());

        // Type field
        Type type = m_entity->GetType();
        IndentedAttributeLabel("Type", m_textValueSplit);
        ImGui::SameLine(0.0f, m_textValueSpacing);
        ImGui::Text(type.GetTypeName().c_str());

        std::vector<Type> allTypes{type};
        ComputeAllBases(type, allTypes);

        for (int i = (int)allTypes.size() - 1; i >= 0; i--) {
            type = allTypes[i];

            if (!type.IsValid())
                continue;

            const EntityRegistry &registry = EntityRegistry::Get();
            const std::vector<std::string> &names = registry.GetAttributeNames(type);

            if (names.empty())
                continue;

            bool shouldCreateHeader = true;
            bool opened = false;

            for (const auto& name: names) {
                AttributeValue atValue;
                m_entity->GetAttribute(name, atValue);

                auto addChannelFn = FindAddChannelFn(atValue.GetTypeName());
                if (!addChannelFn)
                    continue;

                // Creating the collapsing header only if we found a createChannelFn
                // and if it has not being created yet
                if (shouldCreateHeader) {
                    opened = ImGui::CollapsingHeader(type.GetTypeName().c_str());
                    shouldCreateHeader = false;
                }

                if (!opened)
                    break;

                addChannelFn(m_entity, name, atValue);
            }
        }
    }

    void AttributeViewWidget::PostRender() {
    }

    AttributeViewWidget::AttributeViewWidget() : Widget("Attribute View"), m_entity(nullptr) {
        SetWindowFlags(ImGuiWindowFlags_MenuBar);

        m_addChannelFunctions[typeid(glm::vec3).name()] = BIND_ADD_CHANNEL_FN(AddVec3Channel);
    }

    AttributeViewWidget::AddChannelFn AttributeViewWidget::FindAddChannelFn(const std::string &typeName) {
        const auto it = m_addChannelFunctions.find(typeName);
        if (it != m_addChannelFunctions.end()) {
            return it->second;
        }

        if (m_showUnsupportedAttributes)
            return BIND_ADD_CHANNEL_FN(AddUnsupportedChannel);

        return nullptr;
    }

}
