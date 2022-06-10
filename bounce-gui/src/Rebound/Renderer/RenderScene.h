//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_RENDERSCENE_H
#define RBND_RENDERSCENE_H

#include "Material.h"

#include "Rebound/Scene/Entity.h"

#include <unordered_map>
#include <set>


namespace Rebound {

    class RenderDelegate;
    class RenderEntity;

    enum EntityInvalidationType {
        Null                  = 0,
        Added                 = 1 << 0,
        Deleted               = 1 << 1,
        VisibilityChanged     = 1 << 2,
        TransformChanged      = 1 << 3,
        TopologyChanged       = 1 << 4,
        MaterialAssignation   = 1 << 5,
        CompleteInvalidation  = 1 << 6,
    };

    struct EntityInvalidation {
        EntityInvalidationType type;
        std::set<std::string> attributes;
    };

    typedef std::unordered_map<EntityDataHandle, EntityInvalidation> EntityInvalidationMap;
    typedef std::unordered_map<EntityDataHandle, RenderEntity*> RenderIndex;
    typedef std::unordered_map<MaterialHandle, std::shared_ptr<Material>> MaterialIndex;

    class RenderScene {
    public:
        explicit RenderScene(RenderDelegate* delegate);
        ~RenderScene();

        void BindScene(Scene *scene);
        void UnbindScene();

        inline bool IsUpToDate() const { return m_invalidations.empty(); }
        void Sync();
        void Clear();

        Entity GetEntity(const EntityDataHandle& handle) const;
        std::shared_ptr<Material> GetMaterial(const MaterialHandle& handle) const;

        inline RenderIndex GetRenderIndex() const { return m_renderIndex; }

    private:
        bool AddRenderEntity(const EntityDataHandle& handle);
        bool AddMaterial(const MaterialHandle& handle);
        void DeleteRenderEntity(const EntityDataHandle& handle);

        void OnEntityAdded(Entity &entity);
        void OnEntityInvalidated(const EntityDataHandle &entityHandle,
                                 const EntityInvalidation &invalidation);

        RenderIndex m_renderIndex;
        MaterialIndex m_materialIndex;
        EntityInvalidationMap m_invalidations;

        Scene* m_scene;  // TODO: Should probably be a weak pointer

        RenderDelegate* m_renderDelegate;
    };

}

#endif //RBND_RENDERSCENE_H
