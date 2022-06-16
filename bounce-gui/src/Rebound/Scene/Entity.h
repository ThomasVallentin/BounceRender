//
// Created by Margaux TAMIC on 25/03/2022.
//

#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include "Rebound/Core/Rebound.h"

#include "Type.h"
#include "EntityRegistry.h"
#include "AttributeValue.h"
#include "Scene.h"

#include <unordered_map>
#include <any>
#include <array>


namespace Rebound {

#define ENTITY_TYPE(NewType) \
    static inline void Define() { Type::Define<NewType>(#NewType); } \
    static inline Type GetStaticType() { return Type::Find<NewType>(); } \
    static std::vector<AttributeSpec> GetAttributeDefaults(); \
    static inline std::vector<AttributeSpec> GetAllAttributeDefaults() { return GetAttributeDefaults(); } \
    static std::vector<std::string> GetAttributeNames(); \
    static inline std::vector<std::string> GetAllAttributeNames() { return GetAttributeNames(); } \

#define FIND_ENTITY_TYPE(EntityType) Type::Find<EntityType>()
#define ENTITY_TYPE_FROM_BASES(NewType, ...) \
    static inline void Define() { Type::Define<NewType>( \
        #NewType,                            \
        { CALL_MACRO_FOR_EACH(FIND_ENTITY_TYPE, __VA_ARGS__) } ); \
    } \
    static inline Type GetStaticType() { return Type::Find<NewType>(); } \
    static std::vector<std::string> GetAttributeNames(); \
    static std::vector<AttributeSpec> GetAttributeDefaults(); \
    static std::vector<std::string> GetAllAttributeNames(); \
    static std::vector<AttributeSpec> GetAllAttributeDefaults();

#define ADD_ATTR_DEFAULTS(Type) \
for (const auto& spec : Type::GetAttributeDefaults()) { result.push_back(spec); }

#define ADD_ATTR_NAMES(Type) \
for (const auto& name : Type::GetAttributeNames()) { result.push_back(name); }

#define ALL_ATTRIBUTE_FUNCTIONS_FROM_BASES(Type, ...) \
std::vector<std::string> Type::GetAllAttributeNames() { \
    auto result = GetAttributeNames(); \
    CALL_MACRO_FOR_EACH(ADD_ATTR_NAMES, __VA_ARGS__)  \
    return result; \
} \
std::vector<AttributeSpec> Type::GetAllAttributeDefaults() { \
    auto result = GetAttributeDefaults(); \
    CALL_MACRO_FOR_EACH(ADD_ATTR_DEFAULTS, __VA_ARGS__) \
    return result;\
}


    class Entity {
    public:

        // == NAMING ==

        inline std::string GetName() const {
            return m_scene->GetName(this);
        }

        inline void SetName(const std::string &name) const {
            m_scene->SetName(this, name);
        }

        ENTITY_TYPE(Entity)

        inline Type GetType() const { return m_scene->GetType(this); }
        inline std::string GetTypeName() const { return GetType().GetTypeName(); }

        // == HIERARCHY ==

        inline Entity GetParent() const {
            return m_scene->GetParent(this);
        }

        inline uint32_t GetChildCount() const {
            return m_scene->GetChildCount(this);
        }

        inline Entity GetChild(const uint32_t &index) const {
            return m_scene->GetChild(this, index);
        }

        inline bool AddChild(const Entity *child) {
            return m_scene->AddChild(this, child);
        }

        inline bool RemoveChild(const Entity *child) {
            return m_scene->RemoveChild(this, child);
        }

        // == ATTRIBUTES ==

        template<typename T>
        bool GetAttribute(const std::string &name, T &value) const {
            AttributeValue atValue;
            m_scene->GetAttribute(this, name, atValue);
            return atValue.As<T>(value);
        }
        inline bool GetAttribute(const std::string &name, AttributeValue &value) const {
            return m_scene->GetAttribute(this, name, value);
        }

        template<typename T>
        bool SetAttribute(const std::string &name, const T &value) {
            return m_scene->SetAttribute(this,
                                         name,
                                         AttributeValue::Cast<T>(value));
        }

        bool IsValid() const {
            return (m_dataHandle && m_scene);
        }

        inline bool operator==(const Entity& other) const {
            return m_dataHandle == other.m_dataHandle && m_scene == other.m_scene;
        }

        inline EntityDataHandle GetHandle() const { return m_dataHandle; }
        inline Scene *GetScene() const { return m_scene; }

        template <class EntityType>
        inline bool IsA() const { return GetType().IsA<EntityType>(); }

        template <class EntityType>
        inline bool Is() const { return GetType() == Type::Find<EntityType>(); }

        template <class EntityType>
        inline EntityType As() const { return EntityType(m_dataHandle, m_scene); }

    protected:
        Entity() = default;

        Entity(const EntityDataHandle &dataHandle, Scene *scene)
                : m_dataHandle(dataHandle), m_scene(scene) {}

    private:
        friend Scene;

        EntityDataHandle m_dataHandle;
        Scene *m_scene;
    };

}

template <>
class std::hash<Rebound::Entity> {
public:
    size_t operator()(const Rebound::Entity& entity) const {
        // TODO(tvallentin): Will need a proper implementation later
        return entity.GetHandle();
    }

};

#endif //TEST_ENTITY_H
