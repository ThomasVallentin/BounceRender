//
// Created by Thomas Vallentin on 22/05/2022.
//

#include "Mesh.h"
#include "Rebound/Renderer/Hop/Mesh.h"


namespace Hop {

    Mesh::Mesh(const Rebound::Entity &entity)
            : Rebound::RenderMesh(entity) {

    }

    void Mesh::Sync(const Rebound::EntityInvalidation &invalidation) {

    }

}
