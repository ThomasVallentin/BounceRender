//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "Xform.h"

namespace Rebound {

    glm::mat4 Xform::GetLocalMatrix() const {
        glm::mat4 result;
        GetAttribute<glm::mat4>("localMatrix", result);
        return result;
    }

    void Xform::SetLocalMatrix(const glm::mat4 &matrix) {
        SetAttribute<glm::mat4>("localMatrix", matrix);
    }

    glm::mat4 Xform::ComputeLocalToWorldMatrix() const {
        // TODO(tvallentin): Implement this
        return GetLocalMatrix();
    }

    std::vector<AttributeSpec> Xform::GetDefaultAttributes() {
        auto specs = Entity::GetDefaultAttributes();
        specs.emplace_back("localMatrix", AttributeValue::Cast<glm::mat4>({
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1}));

        return specs;
    }

}
