//
// Created by Thomas Vallentin on 10/04/2022.
//

#ifndef BOUNCE_LINE_H
#define BOUNCE_LINE_H

#include "Xform.h"

#include <glm/glm.hpp>

namespace Rebound {

    class Line : public Xform {
    public:

        ENTITY_TYPE_FROM_BASES(Line, Xform)

        std::vector<glm::vec3> GetPositions();
        void SetPositions(const std::vector<glm::vec3> &positions);

        std::vector<uint32_t> GetIndices();
        void SetIndices(const std::vector<uint32_t> &indices);

    protected:
        Line() = default;

        Line(const EntityDataHandle &dataHandle, Scene *scene)
                : Xform(dataHandle, scene) {}

    private:
        friend Scene;
        friend Entity;

    };

}

#endif //BOUNCE_LINE_H
