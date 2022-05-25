//
// Created by Thomas Vallentin on 22/05/2022.
//

#ifndef RBND_LINE_H
#define RBND_LINE_H


#include "RenderEntity.h"

namespace Rebound {

    class RenderLine : public RenderEntity {
    public:
        RenderLine(const Entity& entity) : RenderEntity(entity) {}

        void Sync(const EntityInvalidation& invalidation) override;
        void GetPositions() const;
    };

}


#endif //RBND_LINE_H
