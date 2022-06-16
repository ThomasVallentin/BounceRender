//
// Created by Thomas Vallentin on 01/06/2022.
//

#include "Mesh.h"
#include "DrawItem.h"

#include "Rebound/Renderer/RenderScene.h"

#include <glm/gtx/string_cast.hpp>

namespace Hop {


    void RenderMesh::Sync(const Rebound::EntityInvalidation &invalidation) {
        // TODO: Extremely simple implementation, we flush and recreate the draw items each time
        //  an invalidation happens
        m_drawItems.clear();

        if (invalidation.type & Rebound::EntityInvalidationType::Deleted)
            return;

        auto vtxArray = VertexArray::Create();

        // Vertex Buffer
        std::vector<glm::vec3> positions = GetPositions();
        glm::mat4 worldMatrix = ComputeLocalToWorldMatrix();
        for (auto &pos : positions) {
            auto pos_ = worldMatrix * glm::vec4(pos, 1.0);
            pos = glm::vec3(pos_);
        }

        float *vertices = new float[positions.size() * 3];

        for (size_t i = 0; i < positions.size() ; i++) {
            vertices[i * 3] = positions[i].x;
            vertices[i * 3 + 1] = positions[i].y;
            vertices[i * 3 + 2] = positions[i].z;
        }

        std::shared_ptr<VertexBuffer> vtxBuffer = VertexBuffer::Create(
                vertices,
                positions.size() * 3 * sizeof(float));
        vtxBuffer->SetLayout({{ShaderDataType::Float3, "a_Position"}});

        // Index Buffer
        auto indices = GetIndices();

        std::shared_ptr<IndexBuffer> idxBuffer = IndexBuffer::Create(
                indices.data(),
                indices.size() * sizeof(int));

        vtxArray->AddVertexBuffer(vtxBuffer);
        vtxArray->SetIndexBuffer(idxBuffer);

        m_drawItems.push_back(std::make_shared<DrawItem>(vtxArray,
                                                         DrawType::Mesh,
                                                         m_materialHandle));

        delete[] vertices;
    }
}
