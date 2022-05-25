//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "RenderScene.h"
#include "RenderDelegate.h"

#include "Rebound/Core/Logging.h"


namespace Rebound {

//    void RenderScene::AddEntity(const Entity &entity) {
//        // Entity is already part of the render scene -> return
//        if (m_items.find(entity) != m_items.end()) {
//            return;
//        }
//
//        if (entity.Is<Mesh>()) {
//
//            Mesh mesh = entity.As<Mesh>();
//            auto vtxArray = VertexArray::Create();
//            vtxArray->Bind();
//
//            // Vertex Buffer
//            auto positions = mesh.GetPositions();
//            float *vertices = new float[positions.size() * 3];
//
//            for (size_t i = 0; i < positions.size() ; i++) {
//                vertices[i * 3] = positions[i].x;
//                vertices[i * 3 + 1] = positions[i].y;
//                vertices[i * 3 + 2] = positions[i].z;
//            }
//
//            std::shared_ptr<VertexBuffer> vtxBuffer = VertexBuffer::Create(
//                    vertices,
//                    positions.size() * 3 * sizeof(float));
//            vtxBuffer->SetLayout({{ShaderDataType::Float3, "a_Position"}});
//
//            // Index Buffer
//            auto indices = mesh.GetIndices();
//
//            std::shared_ptr<IndexBuffer> idxBuffer = IndexBuffer::Create(
//                    indices.data(),
//                    indices.size() * sizeof(int));
//
//            vtxArray->AddVertexBuffer(vtxBuffer);
//            vtxArray->SetIndexBuffer(idxBuffer);
//
//            m_items[entity] = new DrawItems::Mesh(vtxArray, m_defaultMaterial);
//        }
//
//        else if (entity.Is<Line>()) {
//
//            Line line = entity.As<Line>();
//            auto vtxArray = VertexArray::Create();
//            vtxArray->Bind();
//
//            // Vertex Buffer
//            auto positions = line.GetPositions();
//            float *vertices = new float[positions.size() * 3];
//
//            for (size_t i = 0; i < positions.size() ; i++) {
//                vertices[i * 3] = positions[i].x;
//                vertices[i * 3 + 1] = positions[i].y;
//                vertices[i * 3 + 2] = positions[i].z;
//            }
//
//            std::shared_ptr<VertexBuffer> vtxBuffer = VertexBuffer::Create(
//                    vertices,
//                    positions.size() * 3 * sizeof(float));
//            vtxBuffer->SetLayout({{ShaderDataType::Float3, "a_Position"}});
//
//            // Index Buffer
//            auto indices = line.GetIndices();
//
//            std::shared_ptr<IndexBuffer> idxBuffer = IndexBuffer::Create(
//                    indices.data(),
//                    indices.size() * sizeof(int));
//
//            vtxArray->AddVertexBuffer(vtxBuffer);
//            vtxArray->SetIndexBuffer(idxBuffer);
//
//            m_items[entity] = new DrawItems::Line(vtxArray, m_defaultMaterial);
//        }
//    }

    RenderScene::RenderScene(RenderDelegate *delegate)
            : m_delegate(delegate),
              m_scene(nullptr) {
    }

    RenderScene::~RenderScene() {
        Flush();
    }

    void RenderScene::BindScene(Scene *scene) {
        if (m_scene) {
            UnbindScene();
        }

        m_scene = scene;

        // Add all entities from the scene
        for (const auto root: m_scene->GetRootEntities()) {
            m_scene->Traverse(&root,
                              [this](Entity entity) {
                                  OnEntityAdded(entity);
                              });
        }
    }

    void RenderScene::UnbindScene() {
        if (m_scene) {
            Flush();
        }

        m_scene = nullptr;
    }

    void RenderScene::Sync() {
        for (const auto &invalidation: m_invalidations) {
            // Entity added case
            if (invalidation.type & EntityInvalidationType::Added) {
                AddRenderEntity(invalidation.entityHandle);

            // Entity deleted case
            } else if (invalidation.type & EntityInvalidationType::Deleted) {
                DeleteRenderEntity(invalidation.entityHandle);

            // Entity updated case
            } else {
                auto it = m_renderIndex.find(invalidation.entityHandle);
                if (it != m_renderIndex.end())
                    it->second->Sync(invalidation);

            }
        }
    }


    void RenderScene::Flush() {
        for (auto &it: m_renderIndex) {
            delete it.second;
        }

        m_renderIndex.clear();
    }

    void RenderScene::OnEntityAdded(Entity &entity) {
        OnEntityInvalidated({entity.GetHandle(), EntityInvalidationType::Added});
    }

    void RenderScene::OnEntityInvalidated(const EntityInvalidation &invalidation) {
        for (auto &inv : m_invalidations) {
            if (inv.entityHandle == invalidation.entityHandle) {
                inv.type = EntityInvalidationType(inv.type | invalidation.type);
                for (const auto& attr : invalidation.attributes)
                    inv.attributes.insert(attr);
            }
        }
    }

    void RenderScene::AddRenderEntity(const EntityDataHandle &handle) {
        if (m_renderIndex.find(handle) == m_renderIndex.end()) {
            RenderEntity *rEntity = m_delegate->CreateRenderEntity(handle);

            if (rEntity) {
                m_renderIndex[handle] = rEntity;
            }
        }
    }

    void RenderScene::DeleteRenderEntity(const EntityDataHandle &handle) {
        auto it = m_renderIndex.find(handle);

        if (it == m_renderIndex.end())
            return;

        delete it->second;
        m_renderIndex.erase(it);
    }

}
