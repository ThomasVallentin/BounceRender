//
// Created by Thomas Vallentin on 27/04/2022.
//

#ifndef RBND_RENDERENTITY_H
#define RBND_RENDERENTITY_H

#include "Material.h"
#include "DrawItem.h"

#include "Rebound/Scene/Entity.h"

#include <glm/glm.hpp>


namespace Rebound {

    struct EntityInvalidation;

    class RenderEntity {
    public:
        RenderEntity(const Entity& entity,
                     const MaterialHandle &materialHandle) :
                m_entity(entity),
                m_materialHandle(materialHandle) {}

        virtual ~RenderEntity() = default;

        virtual void Sync(const EntityInvalidation& invalidation) = 0;

        inline std::vector<std::shared_ptr<DrawItem>> GetDrawItems() const { return m_drawItems; }

        glm::mat4 ComputeLocalToWorldMatrix() const;

    protected:
        const Entity m_entity;
        std::vector<std::shared_ptr<DrawItem>> m_drawItems;

        // TODO: This goes against the principle of having multiple DrawItems by
        //       RenderEntity. It should be implemented in a better way, so that
        //       the RenderEntity can ask the Delegate/Scene for its assignation
        //       info and generate DrawItems that have a single material assigned.
        MaterialHandle m_materialHandle;
    };

}


#endif //RBND_RENDERENTITY_H
