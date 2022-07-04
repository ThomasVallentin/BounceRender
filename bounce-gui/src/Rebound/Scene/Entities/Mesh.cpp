//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "Mesh.h"

namespace Rebound {

    void Mesh::SetIndices(const std::vector<uint32_t> &indices) {
        SetAttribute<std::vector<uint32_t>>("indices", indices);
    }

    std::vector<AttributeSpec> Mesh::GetAttributeDefaults() {
        return { {"positions", {}},
                 {"normals",   {}},
                 {"indices",   {}} };
    }

    std::vector<std::string> Mesh::GetAttributeNames() {
        return {"positions", "normals", "indices"};
    }

    ALL_ATTRIBUTE_FUNCTIONS_FROM_BASES(Mesh, Xform)

    // == ATTRIBUTE ACCESSORS ==

    bool Mesh::GetPositions(std::vector<glm::vec3> &result) {
        GetAttribute<std::vector<glm::vec3>>("positions", result);
        return true;
    }

    void Mesh::SetPositions(const std::vector<glm::vec3> &positions) {
        SetAttribute<std::vector<glm::vec3>>("positions", positions);
    }

    bool Mesh::GetNormals(std::vector<glm::vec3> &normals) {
        GetAttribute<std::vector<glm::vec3>>("normals", normals);
        return true;
    }

    void Mesh::SetNormals(const std::vector<glm::vec3> &normals) {
        SetAttribute<std::vector<glm::vec3>>("normals", normals);
    }

    bool Mesh::GetIndices(std::vector<uint32_t> &indices) {
        GetAttribute<std::vector<uint32_t>>("indices", indices);
        return true;
    }
}