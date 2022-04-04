//
// Created by Margaux TAMIC on 25/03/2022.
//

#ifndef TEST_ENTITYREGISTRY_H
#define TEST_ENTITYREGISTRY_H

#include "AttributeValue.h"

#include <unordered_map>
#include <any>
#include <iostream>


namespace Rebound {


    typedef std::unordered_map<std::string, AttributeValue> AttributeRegistry;
    typedef std::pair<std::string, AttributeValue> AttributeSpec;


    class EntityRegistry {
    public:
        EntityRegistry(const EntityRegistry &) = delete;

        static EntityRegistry &Get() { return s_registry; }

        // TODO(tvallentin): All these methodes may need to be static methods
        //  that returns values from s_registry since the Registry is a singleton

        template<class EntityType>
        void RegisterEntityType() {
            AttributeRegistry atRegistry;
            for (AttributeSpec &spec: EntityType::GetDefaultAttributes()) {
                atRegistry[spec.first] = spec.second;
            }
            m_registry[&typeid(EntityType)] = atRegistry;
        }

        // Get defaults
        bool GetDefaultValue(const type_info *typeInfo,
                             const std::string &name,
                             AttributeValue &atValue) const;

        template<class EntityType>
        inline bool GetDefaultValue(const std::string &name,
                                    AttributeValue &atValue) {
            return GetDefaultValue(&typeid(EntityType), name, atValue);
        }

    private:
        EntityRegistry() = default;

        std::unordered_map<const std::type_info *, AttributeRegistry> m_registry;

        static EntityRegistry s_registry;
    };

}

#endif //TEST_ENTITYREGISTRY_H
