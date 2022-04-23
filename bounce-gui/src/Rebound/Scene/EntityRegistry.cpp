//
// Created by Margaux TAMIC on 25/03/2022.
//

#include <map>
#include "EntityRegistry.h"
#include "AttributeValue.h"


namespace Rebound {

    EntityRegistry EntityRegistry::s_registry;

    bool EntityRegistry::GetDefaultValue(const Type& type, const std::string &name,
                                         AttributeValue &atValue) const {
        auto it = m_registry.find(type);
        if (it != m_registry.end()) {
            auto attributeIt = it->second.attributes.find(name);
            if (attributeIt != it->second.attributes.end()) {
                atValue = attributeIt->second;
                return true;
            }
        }

        return false;
    }

    const AttributeMap *EntityRegistry::GetDefaultValues(const Type &type) {
        const auto it = m_registry.find(type);

        if (it == m_registry.end()) {
            return nullptr;
        }

        return &it->second.attributes;
    }

    std::vector<std::string> EntityRegistry::GetAttributeNames(const Type &type) const {
        const auto it = m_registry.find(type);
        if (it == m_registry.end())
            return {};

        return it->second.attributeNames;
    }

    std::vector<std::string> EntityRegistry::GetAllAttributeNames(const Type &type) const {
        const auto it = m_registry.find(type);
        if (it == m_registry.end())
            return {};

        return it->second.allAttributeNames;
    }

}
