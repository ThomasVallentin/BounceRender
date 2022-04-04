//
// Created by Thomas Vallentin on 31/03/2022.
//

#include "Scene.h"

#include "EntityRegistry.h"
#include "Entity.h"
#include "Entities/Xform.h"


namespace Rebound {

    // == CONSTRUCTORS ==

    Scene *Scene::Open(const std::string &name) {
        auto scene = Scene::New();

        // TODO(tvallentin): This is just a placeholder to be able to use Open
        //  even though Scene serialization/deserialization has not been written yet.

        auto parent = scene->CreateEntity<Entity>("parent");
        scene->CreateEntity<Entity>("child", &parent);

        auto otherParent = scene->CreateEntity<Xform>("other_parent");
        auto otherChild = scene->CreateEntity<Xform>("other_child", &otherParent);
        scene->CreateEntity<Xform>("other_subChild", &otherChild);
        scene->CreateEntity<Xform>("other_sibling", &otherParent);

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
}
