//
// Created by Thomas Vallentin on 22/05/2022.
//

#ifndef RBND_RENDER_MESH_H
#define RBND_RENDER_MESH_H

#include "RenderEntity.h"

#include <glm/vec3.hpp>


namespace Rebound {

    class RenderMesh : public RenderEntity {
    public:
        RenderMesh(const Entity& entity,
                   const MaterialHandle& materialHandle) :
                RenderEntity(entity, materialHandle) {}

        bool GetPositions(std::vector<glm::vec3> &positions) const;
        bool GetNormals(std::vector<glm::vec3> &normals) const;
        bool GetIndices(std::vector<uint32_t> &indices) const;
    };

}


#endif //RBND_RENDER_MESH_H
