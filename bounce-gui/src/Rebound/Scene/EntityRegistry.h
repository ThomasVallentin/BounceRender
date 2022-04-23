//
// Created by Margaux TAMIC on 25/03/2022.
//

#ifndef TEST_ENTITYREGISTRY_H
#define TEST_ENTITYREGISTRY_H

#include "AttributeValue.h"
#include "Type.h"

#include <unordered_map>
#include <any>
#include <iostream>


namespace Rebound {


    typedef std::unordered_map<std::string, AttributeValue> AttributeMap;
    typedef std::pair<std::string, AttributeValue> AttributeSpec;

    struct EntityTypeDefinition {
        std::unordered_map<std::string, AttributeValue> attributes;
        std::vector<std::string> allAttributeNames;
        std::vector<std::string> attributeNames;
    };

    class EntityRegistry {
    public:
        EntityRegistry(const EntityRegistry &) = delete;

        static EntityRegistry &Get() { return s_registry; }

        // TODO(tvallentin): All these methodes may need to be static methods
        //  that returns values from s_registry since the Registry is a singleton

        template<class EntityType>
        void RegisterEntityType() {
            Type type = Type::Find<EntityType>();
            if (!type)
                return;

            EntityTypeDefinition def;
            def.attributeNames = EntityType::GetAttributeNames();
            def.allAttributeNames = EntityType::GetAllAttributeNames();
            for (AttributeSpec &spec: EntityType::GetAllAttributeDefaults()) {
                def.attributes[spec.first] = spec.second;
            }

            m_registry[type] = def;
        }

        // Get defaults
        template<class EntityType>
        inline bool GetDefaultValue(const std::string &name,
                                    AttributeValue &atValue) {
            return GetDefaultValue(Type::Find<EntityType>(), name, atValue);
        }

        bool GetDefaultValue(const Type& typeInfo,
                             const std::string &name,
                             AttributeValue &atValue) const;

        template<class EntityType>
        inline const AttributeMap *GetDefaultValues() {
            return GetDefaultValues(Type::Find<EntityType>());
        }
        const AttributeMap *GetDefaultValues(const Type& type);

        template<class EntityType>
        inline std::vector<std::string> GetAttributeNames() const{
            return GetAttributeNames(Type::Find<EntityType>());
        }
        std::vector<std::string> GetAttributeNames(const Type& type) const;
        std::vector<std::string> GetAllAttributeNames(const Type& type) const;

    private:
        EntityRegistry() = default;

        std::unordered_map<Type, EntityTypeDefinition> m_registry;

        static EntityRegistry s_registry;
    };

}

#endif //TEST_ENTITYREGISTRY_H
