//
// Created by Thomas Vallentin on 22/05/2022.
//

#include "Mesh.h"

#include "Rebound/Scene/Entities/Mesh.h"


namespace Rebound {

    bool RenderMesh::GetPositions(std::vector<glm::vec3> &positions) const {
        auto mesh = m_entity.As<Mesh>();
        return mesh.GetPositions(positions);
    }

    bool RenderMesh::GetNormals(std::vector<glm::vec3> &normals) const {
        auto mesh = m_entity.As<Mesh>();
        return mesh.GetNormals(normals);
    }

    bool RenderMesh::GetIndices(std::vector<uint32_t> &indices) const {
        auto mesh = m_entity.As<Mesh>();
        return mesh.GetIndices(indices);
    }

}
