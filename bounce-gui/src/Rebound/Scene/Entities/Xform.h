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

        ENTITY_TYPE_FROM_BASES(Xform, Entity)

        glm::vec3 GetTranslate() const;
        void SetTranslate(const glm::vec3 &translate);
        glm::vec3 GetRotate() const;
        void SetRotate(const glm::vec3 &rotate);
        glm::vec3 GetScale() const;
        void SetScale(const glm::vec3 &scale);

        glm::mat4 ComputeLocalMatrix() const;
        glm::mat4 ComputeLocalToWorldMatrix() const;

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
