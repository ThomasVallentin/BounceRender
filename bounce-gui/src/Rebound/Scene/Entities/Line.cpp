//
// Created by Thomas Vallentin on 10/04/2022.
//

#include "Line.h"

namespace Rebound {

    std::vector<AttributeSpec> Line::GetAttributeDefaults() {
        return { {"positions", {}},
                 {"indices",   {}} };
    }

    std::vector<std::string> Line::GetAttributeNames() {
        return {"positions", "indices"};
    }

    ALL_ATTRIBUTE_FUNCTIONS_FROM_BASES(Line, Xform)

    // == ATTRIBUTE ACCESSORS ==

    std::vector<glm::vec3> Line::GetPositions() {
        std::vector<glm::vec3> result;
        GetAttribute<std::vector<glm::vec3>>("positions", result);

        return result;
    }

    void Line::SetPositions(const std::vector<glm::vec3> &positions) {
        SetAttribute<std::vector<glm::vec3>>("positions", positions);
    }

    std::vector<uint32_t> Line::GetIndices() {
        std::vector<uint32_t> result;
        GetAttribute<std::vector<uint32_t>>("indices", result);

        return result;
    }

    void Line::SetIndices(const std::vector<uint32_t> &indices) {
        SetAttribute<std::vector<uint32_t>>("indices", indices);
    }
}
