//
// Created by Thomas Vallentin on 01/04/2022.
//

#ifndef RBND_SCENEHIERARCHYPANEL_H
#define RBND_SCENEHIERARCHYPANEL_H

#include "Rebound/Core/Widget.h"
#include "Rebound/Scene/Scene.h"
#include "Rebound/Scene/Entity.h"

#include <memory>
#include <utility>


namespace Rebound {

    class SceneHierarchyWidget : public Widget {
    public:
        SceneHierarchyWidget() : Widget("Scene Hierarchy") {}
        explicit SceneHierarchyWidget(std::shared_ptr<Scene> scene) : m_scene(std::move(scene)), Widget("Scene Hierarchy") {}

        void SetScene(const std::shared_ptr<Scene> &scene);

        void PreRender() override;
        void Render() override;
        void PostRender() override;

        // == SELECTION ==

        inline std::vector<Entity> &Selection() {
            return m_selection;
        }

        inline bool IsSelected(const Entity &entity) const {
            return std::find(m_selection.begin(), m_selection.end(), entity) != m_selection.end();
        }

        inline void SelectEntity(const Entity &entity) {
            if (!IsSelected(entity))
                m_selection.push_back(entity);
        }

        inline void DeselectEntity(const Entity &entity) {
            if (IsSelected(entity))
                std::remove(m_selection.begin(), m_selection.end(), entity);
        }

        inline void ClearSelection() {
            m_selection.clear();
        }

    private:
        void RecurseEntity(const Entity& entity);

        std::shared_ptr<Scene> m_scene;
        std::vector<Entity> m_selection;
    };

}

#endif //RBND_SCENEHIERARCHYPANEL_H
