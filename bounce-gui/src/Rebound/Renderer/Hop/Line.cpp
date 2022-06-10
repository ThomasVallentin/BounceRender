//
// Created by Thomas Vallentin on 01/06/2022.
//

#include "Line.h"
#include "DrawItem.h"

#include "Rebound/Renderer/RenderScene.h"


namespace Hop {

    void RenderLine::Sync(const Rebound::EntityInvalidation &invalidation) {
        // TODO: Extremely simple implementation, we flush the draw item each time an invalidation
        //       happens
        if (!m_drawItems.empty()) {
            m_drawItems.clear();
        }

        if (invalidation.type & Rebound::EntityInvalidationType::Deleted)
            return;

        auto vtxArray = VertexArray::Create();
        vtxArray->Bind();

        // Vertex Buffer
        auto positions = GetPositions();
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
                                                         DrawType::Line,
                                                         m_materialHandle));

        delete[] vertices;
    }
}