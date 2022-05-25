//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_RENDERSCENE_H
#define RBND_RENDERSCENE_H

#include <unordered_map>
#include <set>
#include "RenderEntity.h"

#include "Rebound/Scene/Entity.h"


namespace Rebound {

    class RenderDelegate;

    enum EntityInvalidationType {
        Null                  = 0,
        Added                 = 1 << 0,
        Deleted               = 1 << 1,
        TransformChanged      = 1 << 2,
        TopologyChanged       = 1 << 3,
        CompleteInvalidation  = 1 << 4,
    };

    struct EntityInvalidation {
        EntityDataHandle entityHandle;
        EntityInvalidationType type;
        std::set<std::string> attributes;
    };

    typedef std::vector<EntityInvalidation> EntityInvalidationVector;
    typedef std::unordered_map<EntityDataHandle, RenderEntity*> RenderIndex;

    class RenderScene {
    public:
        explicit RenderScene(RenderDelegate* delegate);
        ~RenderScene();

        void BindScene(Scene *scene);
        void UnbindScene();

        inline bool IsUpToDate() const { return m_invalidations.empty(); }
        void Sync();
        void Flush();

    private:
        void AddRenderEntity(const EntityDataHandle& handle);
        void DeleteRenderEntity(const EntityDataHandle& handle);

        void OnEntityAdded(Entity &entity);
        void OnEntityInvalidated(const EntityInvalidation &invalidation);

        RenderIndex m_renderIndex;
        EntityInvalidationVector m_invalidations;

        Scene* m_scene;  // TODO: Should be a weak pointer

        RenderDelegate* m_delegate;
    };

}

#endif //RBND_RENDERSCENE_H
