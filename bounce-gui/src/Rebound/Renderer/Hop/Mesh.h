//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_RENDER_MESH_H
#define HOP_RENDER_MESH_H

#include "Rebound/Renderer/Mesh.h"

#include <memory>
#include <utility>


namespace Hop {

    class RenderMesh : public Rebound::RenderMesh {
    public:
        RenderMesh(const Rebound::Entity& entity,
                   const Rebound::MaterialHandle& handle) :
                Rebound::RenderMesh(entity, handle) {}

        void Sync(const Rebound::EntityInvalidation &invalidation,
                  Rebound::RenderSharedData* sharedData) override;

    };

}

#endif //HOP_RENDER_MESH_H
