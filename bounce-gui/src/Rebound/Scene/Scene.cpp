//
// Created by Thomas Vallentin on 31/03/2022.
//

#include "Scene.h"

#include "EntityRegistry.h"
#include "Entity.h"
#include "Entities/Xform.h"
#include "Entities/Mesh.h"
#include "Entities/Line.h"


namespace Rebound {

    // == CONSTRUCTORS ==

    Scene *Scene::Open(const std::string &name) {
        auto scene = Scene::New();

        // TODO(tvallentin): This is just a placeholder to be able to use Open
        //  even though Scene serialization/deserialization has not been written yet.

        auto parent = scene->CreateEntity<Entity>("parent");
        auto child = scene->CreateEntity<Entity>("child", &parent);

        auto otherParent = scene->CreateEntity<Xform>("other_parent");
        auto otherChild = scene->CreateEntity<Xform>("other_child", &otherParent);

        auto plane = scene->CreateEntity<Mesh>("plane", &otherChild);
        plane.SetPositions({ {-10.0f, 0.0f, -10.0f},
                             {10.0f,  0.0f, -10.0f},
                             {10.0f,  0.0f, 10.0f},
                             {-10.0f, 0.0f, 10.0f} });
        plane.SetIndices({0, 1, 2, 2, 3, 0});

        auto mesh = scene->CreateEntity<Mesh>("cube", &child);
        mesh.SetPositions({ {-1.0f, 0.0f, -1.0f},
                            {-1.0f, 0.0f, 1.0f},
                            {1.0f,  0.0f, 1.0f},
                            {1.0f,  0.0f, -1.0f},
                            {-1.0f, 1.0f,  -1.0f},
                            {-1.0f, 1.0f,  1.0f},
                            {1.0f,  1.0f,  1.0f},
                            {1.0f,  1.0f,  -1.0f} });
        mesh.SetIndices({0, 1, 2, 2, 3, 0,
                         0, 1, 5, 5, 4, 0,
                         0, 3, 7, 7, 4, 0,
                         1, 2, 6, 6, 5, 1,
                         2, 3, 7, 7, 6, 2,
                         4, 5, 6, 6, 7, 4});

        auto line = scene->CreateEntity<Line>("line", &otherParent);
        line.SetPositions({ {1.73f, -0.85f,  1.29f},
                            {3.74f, 0.56f, 1.59f},
                            {5.03f, 2.76f, 1.14f},
                            {5.55f, 4.98f, 0.29f},
                            {3.51f, 4.47f, -0.48f},
                            {1.97f, 2.64f, -0.33f},
                            {1.07f, 0.33f, 0.37f} });
        line.SetIndices({0, 1, 2, 3, 4, 5, 6});

        return scene;
    }

    // == NAMING ==

    std::string Scene::GetName(const Entity *entity) const {
        return m_data->GetName(entity->m_dataHandle);
    }

    void Scene::SetName(const Entity *entity, const std::string &name) const {
        m_data->SetName(entity->m_dataHandle, name);
    }

    std::string Scene::GetTypeName(const Entity *entity) {
        return m_data->GetTypeName(entity->m_dataHandle);
    }

    // == ATTRIBUTES ==

    bool Scene::GetAttribute(const Entity *entity,
                             const std::string &name,
                             AttributeValue &value) const {
        // Try to find value from scene data or a default value from the registry
        return m_data->GetAttribute(entity->m_dataHandle, name, value);
    }

    bool Scene::SetAttribute(const Entity *entity,
                             const std::string &name,
                             const AttributeValue& value) const {
        return m_data->SetAttribute(entity->m_dataHandle,
                                    name,
                                    value);
    }

    // == HIERARCHY ==

    void Scene::Traverse(const Entity *entity, const TraversalFunction &func) {

        // Transforms the given func as a DataTraversalFunc
        auto dataTraversalFunc =
                [&func, this](const EntityDataHandle &handle) {
                    func(Entity(handle, this));
                };

        m_data->Traverse(entity->m_dataHandle, dataTraversalFunc);
    }

    Entity Scene::GetParent(const Entity *entity) {
        return {m_data->GetParent(entity->m_dataHandle), this};
    }

    uint32_t Scene::GetChildCount(const Entity *entity) const {
        return m_data->GetChildCount(entity->m_dataHandle);
    }

    Entity Scene::GetChild(const Entity *entity, const uint32_t &index) {
        return { m_data->GetChild(entity->m_dataHandle, index), this };
    }

    bool Scene::AddChild(const Entity *parent, const Entity *child) const {
        return m_data->AddChild(parent->m_dataHandle, child->m_dataHandle);
    }

    bool Scene::RemoveChild(const Entity *parent, const Entity *child) const {
        return m_data->RemoveChild(parent->m_dataHandle, child->m_dataHandle);
    }

    std::vector<Entity> Scene::GetRootEntities() {
        std::vector<Entity> roots;
        for (const auto& handle : m_data->GetRootHandles()) {
            roots.push_back( {handle, this} );
        }

        return roots;
    }

    bool Scene::Is(const Entity *entity, const type_info *type) {
        return m_data->Is(entity->m_dataHandle, type);
    }
}
