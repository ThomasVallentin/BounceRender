//
// Created by Thomas Vallentin on 22/05/2022.
//

#ifndef RBND_RENDER_LINE_H
#define RBND_RENDER_LINE_H


#include "RenderEntity.h"

#include <glm/vec3.hpp>


namespace Rebound {

    class RenderLine : public RenderEntity {
    public:
        RenderLine(const Entity& entity,
                   const MaterialHandle& materialHandle) :
                RenderEntity(entity, materialHandle) {}

        std::vector<glm::vec3> GetPositions() const;
        std::vector<uint32_t> GetIndices() const;
    };

}


#endif //RBND_RENDER_LINE_H
