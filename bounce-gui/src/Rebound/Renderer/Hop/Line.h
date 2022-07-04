//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_RENDER_LINE_H
#define HOP_RENDER_LINE_H

#include "Rebound/Renderer/Line.h"

#include <memory>
#include <utility>

namespace Hop {

    class RenderLine : public Rebound::RenderLine {
    public:
        RenderLine(const Rebound::Entity& entity,
                   const Rebound::MaterialHandle& handle) :
                Rebound::RenderLine(entity, handle) {}

        void Sync(const Rebound::EntityInvalidation &invalidation,
                  Rebound::RenderSharedData* sharedData) override;

    };

}


#endif //HOP_RENDER_LINE_H
