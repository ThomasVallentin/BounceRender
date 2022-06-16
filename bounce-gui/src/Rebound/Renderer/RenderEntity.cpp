//
// Created by Thomas Vallentin on 27/04/2022.
//

#include "RenderEntity.h"

#include "Rebound/Scene/Entities/Xform.h"

namespace Rebound {

    glm::mat4 RenderEntity::ComputeLocalToWorldMatrix() const  {
        if (m_entity.IsA<Xform>()) {
            return m_entity.As<Xform>().ComputeLocalToWorldMatrix();
        }

        return glm::mat4(1.0);
    }

}
