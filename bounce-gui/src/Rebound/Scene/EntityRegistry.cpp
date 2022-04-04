//
// Created by Margaux TAMIC on 25/03/2022.
//

#include "EntityRegistry.h"
#include "AttributeValue.h"


namespace Rebound {


    EntityRegistry EntityRegistry::s_registry;

    bool EntityRegistry::GetDefaultValue(const type_info *typeInfo, const std::string &name,
                                         AttributeValue &atValue) const {
        auto it = m_registry.find(typeInfo);
        if (it != m_registry.end()) {
            auto attributeIt = it->second.find(name);
            if (attributeIt != it->second.end()) {
                atValue = attributeIt->second;
                return true;
            }
        }

        return false;
    }


}
