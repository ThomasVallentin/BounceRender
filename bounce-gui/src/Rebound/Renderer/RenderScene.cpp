//
// Created by Thomas Vallentin on 04/04/2022.
//

#include "RenderScene.h"
#include "RenderDelegate.h"
#include "RenderEntity.h"

#include "Rebound/Core/Logging.h"


namespace Rebound {

    RenderScene::RenderScene(RenderDelegate *delegate)
            : m_renderDelegate(delegate),
              m_scene(nullptr) {
    }

    RenderScene::~RenderScene() {
        Clear();
    }

    void RenderScene::BindScene(Scene *scene) {
        if (m_scene) {
            Clear();
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
            Clear();
        }

        m_scene = nullptr;
    }

    void RenderScene::Sync() {
        for (const auto &[entityHandle,
                          invalidation]: m_invalidations) {
            // Entity deleted case
            if (invalidation.type & EntityInvalidationType::Deleted) {
                DeleteRenderEntity(entityHandle);

            // Entity added case
            } else if (invalidation.type & EntityInvalidationType::Added) {
                AddRenderEntity(entityHandle);

            // Entity updated case
            } else {
                auto rIndexIt = m_renderIndex.find(entityHandle);
                if (rIndexIt != m_renderIndex.end())
                    rIndexIt->second->Sync(invalidation);
            }
        }

        // All invalid Entities has been synced, clear the invalidations
        m_invalidations.clear();
    }

    void RenderScene::Clear() {
        for (auto &it: m_renderIndex) {
            delete it.second;
        }

        m_renderIndex.clear();
    }

    void RenderScene::OnEntityAdded(Entity &entity) {
        OnEntityInvalidated(entity.GetHandle(),
                            {EntityInvalidationType::Added } );
    }

    void RenderScene::OnEntityInvalidated(const EntityDataHandle &entityHandle,
                                          const EntityInvalidation &invalidation) {
        auto it = m_invalidations.find(entityHandle);

        // Entity is already invalid, merging the new invalidation with the existing one
        if (it != m_invalidations.end()) {
            it->second.type = EntityInvalidationType(it->second.type | invalidation.type);
            for (const auto &attr: invalidation.attributes)
                it->second.attributes.insert(attr);
        }
        // Entity was still valid, adding the invalidation
        else {
            m_invalidations.insert( {entityHandle, invalidation} );
        }

    }

    bool RenderScene::AddRenderEntity(const EntityDataHandle &handle) {
        if (m_renderIndex.find(handle) == m_renderIndex.end()) {
            RenderEntity *rEntity = m_renderDelegate->CreateRenderEntity(handle);

            if (rEntity) {
                rEntity->Sync({ EntityInvalidationType::Added } );
                m_renderIndex[handle] = rEntity;
                return true;
            }
        }

        return false;
    }

    bool RenderScene::AddMaterial(const MaterialHandle &handle) {
        if (m_materialIndex.find(handle) == m_materialIndex.end()) {
            std::shared_ptr<Material> material = m_renderDelegate->CreateMaterial(handle);

            if (material) {
                m_materialIndex[handle] = material;
                return true;
            }
        }

        return false;
    }

    void RenderScene::DeleteRenderEntity(const EntityDataHandle &handle) {
        auto it = m_renderIndex.find(handle);

        if (it == m_renderIndex.end())
            return;

        delete it->second;
        m_renderIndex.erase(it);
    }

    Entity RenderScene::GetEntity(const EntityDataHandle &handle) const {
        return m_scene->EntityFromHandle(handle);
    }

    std::shared_ptr<Material> RenderScene::GetMaterial(const MaterialHandle &handle) const {
        auto it = m_materialIndex.find(handle);

        if (it != m_materialIndex.end())
            return it->second;

        return nullptr;
    }

}
