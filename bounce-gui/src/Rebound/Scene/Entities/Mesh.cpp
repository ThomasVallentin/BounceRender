//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "Mesh.h"

namespace Rebound {

    std::vector<glm::vec3> Mesh::GetPositions() {
        std::vector<glm::vec3> result;
        GetAttribute<std::vector<glm::vec3>>("positions", result);

        return result;
    }

    void Mesh::SetPositions(const std::vector<glm::vec3> &positions) {
        SetAttribute<std::vector<glm::vec3>>("positions", positions);
    }

    std::vector<AttributeSpec> Mesh::GetDefaultAttributes() {
        auto specs = Xform::GetDefaultAttributes();

        specs.emplace_back("positions", AttributeValue::New<std::vector<glm::vec3>>());
        specs.emplace_back("normals", AttributeValue::New<std::vector<glm::vec3>>());
        specs.emplace_back("indices", AttributeValue::New<std::vector<uint32_t>>());

        return specs;
    }

    std::vector<glm::vec3> Mesh::GetNormals() {
        std::vector<glm::vec3> result;
        GetAttribute<std::vector<glm::vec3>>("normals", result);

        return result;
    }

    void Mesh::SetNormals(const std::vector<glm::vec3> &normals) {
        SetAttribute<std::vector<glm::vec3>>("normals", normals);
    }

    std::vector<uint32_t> Mesh::GetIndices() {
        std::vector<uint32_t> result;
        GetAttribute<std::vector<uint32_t>>("indices", result);

        return result;
    }

    void Mesh::SetIndices(const std::vector<uint32_t> &indices) {
        SetAttribute<std::vector<uint32_t>>("indices", indices);
    }
}