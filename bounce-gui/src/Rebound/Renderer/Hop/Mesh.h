//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_RENDER_MESH_H
#define HOP_RENDER_MESH_H

#include "Rebound/Renderer/Mesh.h"

#include "Item.h"
#include "VertexArray.h"

#include <memory>
#include <utility>


namespace Hop {

    class Mesh : public Rebound::RenderMesh {
    public:
        Mesh(const Rebound::Entity& entity);

        void Sync(const Rebound::EntityInvalidation &invalidation) override;

    };

}

#endif //HOP_RENDER_MESH_H
