//
// Created by Thomas Vallentin on 22/05/2022.
//

#include "Mesh.h"

#include "Rebound/Scene/Entities/Mesh.h"


namespace Rebound {

    std::vector<glm::vec3> RenderMesh::GetPositions() const {
        auto mesh = m_entity.As<Mesh>();
        return mesh.GetPositions();
    }

    std::vector<glm::vec3> RenderMesh::GetNormals() const {
        auto mesh = m_entity.As<Mesh>();
        return mesh.GetNormals();
    }

    std::vector<uint32_t> RenderMesh::GetIndices() const {
        auto mesh = m_entity.As<Mesh>();
        return mesh.GetIndices();
    }

}
