//
// Created by Thomas Vallentin on 27/04/2022.
//

#ifndef RBND_RENDERENTITY_H
#define RBND_RENDERENTITY_H

#include "Material.h"

#include "Rebound/Scene/Entity.h"


namespace Rebound {

    class EntityInvalidation;

    class RenderEntity {
    public:
        RenderEntity(const Entity& entity) : m_entity(entity) {}
        virtual ~RenderEntity() = default;

        virtual void Sync(const EntityInvalidation& invalidation) = 0;

    private:
        const Entity m_entity;
        std::shared_ptr<Material> m_material;
    };

}


#endif //RBND_RENDERENTITY_H
