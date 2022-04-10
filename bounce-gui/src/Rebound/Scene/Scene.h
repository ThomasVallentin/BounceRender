//
// Created by Thomas Vallentin on 31/03/2022.
//

#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "EntityRegistry.h"
#include "AttributeValue.h"
#include "Data.h"

#include <unordered_map>
#include <any>
#include <array>


namespace Rebound {

    class Entity;

    typedef std::function<void(Entity entity)> TraversalFunction;

    class Scene {
    public:

        // == CONSTRUCTORS ==

        inline static Scene *New() { return new Scene(); }
        static Scene *Open(const std::string &name);

        // == ENTITIES ==

        template<class EntityType>
        EntityType CreateEntity(const std::string &name) {
            // TODO(tvallentin): Ensure EntityType is in the registry before instancing it.
            return {m_data->CreateHandle<EntityType>(name), this};
        }

        template<class EntityType>
        EntityType CreateEntity(const std::string &name, const Entity *parent) {
            auto entity = CreateEntity<EntityType>(name);
            AddChild(parent, &entity);

            return entity;
        }

        bool Is(const Entity *entity, const type_info* type);

        // == NAMING ==

        std::string GetName(const Entity *entity) const;
        void SetName(const Entity *entity, const std::string &name) const;
        std::string GetTypeName(const Entity *entity);

        // == ATTRIBUTES ==

        bool GetAttribute(const Entity *entity,
                          const std::string &name,
                          AttributeValue &value) const;
        bool SetAttribute(const Entity *entity,
                          const std::string &name,
                          const AttributeValue& value) const;

        // == HIERARCHY ==

        void Traverse(const Entity *entity, const TraversalFunction &func);

        Entity GetParent(const Entity *entity);
        uint32_t GetChildCount(const Entity *entity) const;
        Entity GetChild(const Entity *entity, const uint32_t& index);
        bool AddChild(const Entity *parent, const Entity *child) const;
        bool RemoveChild(const Entity *parent, const Entity *child) const;

        std::vector<Entity> GetRootEntities();

    private:
        Scene() : m_data(new SceneData) {}

        SceneData *m_data;
    };

}

#endif //TEST_SCENE_H
