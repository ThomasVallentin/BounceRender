//
// Created by Thomas Vallentin on 22/05/2022.
//

#ifndef RBND_MESH_H
#define RBND_MESH_H

#include "RenderEntity.h"

namespace Rebound {

    class RenderMesh : public RenderEntity {
    public:
        RenderMesh(const Entity& entity) : RenderEntity(entity) {}

        void GetPositions() const;
        void GetNormals() const;
        void GetTopology() const;
    };

}



#endif //RBND_MESH_H
