//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "Scene.h"

#include "Rebound/Scene/Entities/Mesh.h"
#include "Rebound/Scene/Entities/Line.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "Buffer.h"
#include "Mesh.h"
#include "Line.h"

#include "Rebound/Core/Logging.h"


namespace Rebound {

    void RenderScene::AddEntity(const Entity &entity) {
        // Entity is already part of the render scene -> return
        if (m_items.find(entity) != m_items.end()) {
            return;
        }

        if (entity.Is<Mesh>()) {

            Mesh mesh = entity.As<Mesh>();
            auto vtxArray = VertexArray::Create();
            vtxArray->Bind();

            // Vertex Buffer
            auto positions = mesh.GetPositions();
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
            auto indices = mesh.GetIndices();

            std::shared_ptr<IndexBuffer> idxBuffer = IndexBuffer::Create(
                    indices.data(),
                    indices.size() * sizeof(int));

            vtxArray->AddVertexBuffer(vtxBuffer);
            vtxArray->SetIndexBuffer(idxBuffer);

            m_items[entity] = new RenderItems::Mesh(vtxArray, m_defaultMaterial);
        }

        else if (entity.Is<Line>()) {

            Line line = entity.As<Line>();
            auto vtxArray = VertexArray::Create();
            vtxArray->Bind();

            // Vertex Buffer
            auto positions = line.GetPositions();
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
            auto indices = line.GetIndices();

            std::shared_ptr<IndexBuffer> idxBuffer = IndexBuffer::Create(
                    indices.data(),
                    indices.size() * sizeof(int));

            vtxArray->AddVertexBuffer(vtxBuffer);
            vtxArray->SetIndexBuffer(idxBuffer);

            m_items[entity] = new RenderItems::Line(vtxArray, m_defaultMaterial);
        }
    }

    void RenderScene::RemoveEntity(const Entity &entity) {
        // Entity is not part of the render scene -> return
        if (m_items.find(entity) == m_items.end()) {
            return;
        }
    }

    void RenderScene::Update() {
        for (auto &it: m_items) {
            if (!it.second->IsValid())
                UpdateItem(it.first, it.second);
        }
    }

    void RenderScene::Submit() {
        for (const auto &it: m_items) {
            Renderer::Submit(it.second);
        }
    }

    void RenderScene::UpdateItem(const Entity &entity, RenderItem *item) {
        RBND_DEBUG("UpdateItem ! %s", entity.GetName().c_str());
    }

    void RenderScene::Invalidate(const Entity &entity) const {
        auto item = GetItem(entity);
        if (item)
            item->Invalidate();
    }

    RenderItem *RenderScene::GetItem(const Entity &entity) const {
        const auto it = m_items.find(entity);
        if (it != m_items.end()) {
            return it->second;
        }

        return nullptr;
    }

}
