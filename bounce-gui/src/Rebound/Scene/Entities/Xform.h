//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_XFORM_H
#define RBND_XFORM_H

#include "Rebound/Scene/Entity.h"
#include "glm/glm.hpp"


namespace Rebound {

    class Xform : public Entity {
    public:
        glm::mat4 GetLocalMatrix() const;
        void SetLocalMatrix(const glm::mat4 &matrix);

        glm::mat4 ComputeLocalToWorldMatrix() const;

        static std::vector<AttributeSpec> GetDefaultAttributes();

    protected:
        Xform() = default;

        Xform(const EntityDataHandle &dataHandle, Scene *scene)
                : Entity(dataHandle, scene) {}

    private:
        friend Scene;
        friend Entity;
    };


}

#endif //RBND_XFORM_H
