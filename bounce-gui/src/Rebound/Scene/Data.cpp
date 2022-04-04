//
// Created by Margaux TAMIC on 25/03/2022.
//

#include "Data.h"
#include "EntityRegistry.h"

#include <unordered_map>
#include <any>
#include <utility>


namespace Rebound {

    // == NAME ==

    std::string SceneData::GetName(const EntityDataHandle &entity) {
        EntityData *data = GetEntityData(entity);
        if (!data)
            return "";

        return data->name;
    }

    void SceneData::SetName(const EntityDataHandle &entity, const std::string &name) {
        EntityData *data = GetEntityData(entity);
        if (!data)
            return;

        data->name = name;
    }

    std::string SceneData::GetTypeName(const EntityDataHandle &entity) {
        EntityData *data = GetEntityData(entity);
        if (!data)
            return "";

        return data->type->name();
    }

    // == ATTRIBUTES ==

    bool SceneData::GetAttribute(const EntityDataHandle &entity,
                                 const std::string &name,
                                 AttributeValue &outValue) const {
        const EntityData *data = GetEntityData(entity);
        if (!data)
            return false;

        // Trying to find the attribute in the entity attributes
        // If names match, set the attribute value
        for (const auto &attr: data->attributes)
            if (attr.first == name) {
                outValue = attr.second;
                return true;
            }

        // Attribute wasn't found trying to get a default value from the registry
        // Note(tvallentin): This may need to be moved outside of the data class since this
        //  is not really abstract. It's here because it allows to get the EntityData only once.
        EntityRegistry &registry = EntityRegistry::Get();
        return registry.GetDefaultValue(data->type, name, outValue);
    }

    bool SceneData::SetAttribute(const EntityDataHandle &entity,
                                 const std::string &name,
                                 AttributeValue value) {
        EntityData *data = GetEntityData(entity);
        if (!data)
            return false;

        // Trying to find the attribute in the entity attributes
        // If names match, set the attribute value
        for (auto &attr: data->attributes)
            if (attr.first == name) {
                attr.second = std::move(value);
                return true;
            }

        data->attributes.emplace_back(name, value);

        // Attribute wasn't found return false
        return false;
    }

    // == HIERARCHY ==

    EntityDataHandle SceneData::GetParent(const EntityDataHandle &entity) const {
        const EntityData *data = GetEntityData(entity);
        return (data) ? data->parent : EntityDataHandle(0);
    }

    bool SceneData::AddChild(const EntityDataHandle &parent,
                             const EntityDataHandle &entity) {
        EntityData *parentData = GetEntityData(parent);
        EntityData *childData = GetEntityData(entity);
        if (!parentData)
            return false;

        // Returning false if the given entity is already child of the parent
        for (const auto &child: parentData->children)
            if (child == entity)
                return false;

        parentData->children.push_back(entity);
        childData->parent = parent;
        return true;
    }

    bool SceneData::RemoveChild(const EntityDataHandle &parent,
                                const EntityDataHandle &entity) {
        EntityData *data = GetEntityData(parent);
        if (!data)
            return false;

        // Remove the data handle from the children vector
        if (std::remove(data->children.begin(),
                        data->children.end(),
                        entity) == data->children.end()) {
            return false;
        }

        return true;
    }

    // == INTERNAL ==

    const SceneData::EntityData *SceneData::GetEntityData(const EntityDataHandle &entity) const {
        // Trying to find the entity handle in the map
        for (auto &thing: m_data) {
            if (entity == thing.first) {
                return &thing.second;;
            }
        }

        return nullptr;
    }

    SceneData::EntityData *SceneData::GetEntityData(const EntityDataHandle &entity) {
        // Trying to find the entity handle in the map
        for (auto &thing: m_data) {
            if (entity == thing.first) {
                return &thing.second;;
            }
        }

        return nullptr;
    }

    void SceneData::Traverse(const EntityDataHandle &entity, const DataTraversalFunc &func) {
        func(entity);

        EntityData *data = GetEntityData(entity);
        if (!data)
            return;

        for (const auto &child : data->children)
            Traverse(child, func);
    }

    uint32_t SceneData::GetChildCount(const EntityDataHandle &entity) const {
        const EntityData *data = GetEntityData(entity);
        if (!data)
            return 0;

        return data->children.size();
    }


    EntityDataHandle SceneData::GetChild(const EntityDataHandle &entity,
                                         const uint32_t &index) const {
        const EntityData *data = GetEntityData(entity);
        if (!data)
            return 0;

        if (index >= data->children.size()) {
            return 0;
        }

        return data->children[index];
    }

    std::vector<EntityDataHandle> SceneData::GetRootHandles() const {
        std::vector<EntityDataHandle> roots;
        for (const auto &it : m_data)
            if (!it.second.parent)
                roots.push_back(it.first);

        return roots;
    }

}
