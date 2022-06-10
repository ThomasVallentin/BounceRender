//
// Created by Thomas Vallentin on 22/05/2022.
//

#include "Line.h"

#include "Rebound/Scene/Entities/Line.h"


namespace Rebound {

    std::vector<glm::vec3> RenderLine::GetPositions() const {
        auto mesh = m_entity.As<Line>();
        return mesh.GetPositions();
    }

    std::vector<uint32_t> RenderLine::GetIndices() const {
        auto mesh = m_entity.As<Line>();
        return mesh.GetIndices();
    }

}
