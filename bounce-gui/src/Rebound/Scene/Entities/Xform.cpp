//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "Xform.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Rebound {

    glm::mat4 Xform::ComputeLocalMatrix() const {
        auto translate = glm::translate(glm::mat4(), GetScale());
        auto rotate = glm::toMat4(glm::quat(GetRotate()));
        auto scale = glm::scale(glm::mat4(), GetScale());

        return translate * rotate * scale;
    }

    glm::mat4 Xform::ComputeLocalToWorldMatrix() const {
        // Going up on each parent trying to find the first Xform parent.
        // The LocalToWorldMatrix equals the LocalToWorldMatrix of this parent multiplied
        // by the local matrix of the current Xform.
        Entity parent = GetParent();
        while (parent.IsValid()) {
            if (parent.IsA<Xform>())
                return parent.As<Xform>().ComputeLocalToWorldMatrix() * ComputeLocalMatrix();

            parent = parent.GetParent();
        }

        // No valid Xform parent was found, the LocalToWorldMatrix is the LocalMatrix.
        return ComputeLocalMatrix();
    }

    std::vector<AttributeSpec> Xform::GetAttributeDefaults() {
        return {{"translate", AttributeValue::Cast<glm::vec3>({0, 0, 0})},
                {"rotate", AttributeValue::Cast<glm::vec3>({0, 0, 0})},
                {"scale", AttributeValue::Cast<glm::vec3>({1, 1, 1})}};
    }

    std::vector<std::string> Xform::GetAttributeNames() {
        return {"translate", "rotate", "scale"};
    }

    ALL_ATTRIBUTE_FUNCTIONS_FROM_BASES(Xform, Entity);

    // == ATTRIBUTE ACCESSORS ==

    glm::vec3 Xform::GetTranslate() const {
        glm::vec3 result;
        GetAttribute("translate", result);
        return result;
    }

    void Xform::SetTranslate(const glm::vec3 &translate) {
        SetAttribute("translate", translate);
    }

    glm::vec3 Xform::GetRotate() const {
        glm::vec3 result;
        GetAttribute("rotate", result);
        return result;
    }

    void Xform::SetRotate(const glm::vec3 &rotate) {
        SetAttribute("rotate", rotate);
    }

    glm::vec3 Xform::GetScale() const {
        glm::vec3 result;
        GetAttribute("scale", result);
        return result;
    }

    void Xform::SetScale(const glm::vec3 &scale) {
        SetAttribute("scale", scale);
    }


}
