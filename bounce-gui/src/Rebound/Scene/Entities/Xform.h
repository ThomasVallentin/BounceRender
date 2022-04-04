//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_XFORM_H
#define RBND_XFORM_H

#include "Rebound/Scene/Entity.h"

typedef std::array<float, 16> Matrix4;

namespace Rebound {

    class Xform : public Entity {
    public:
        inline Matrix4 GetTransform() const {
            Matrix4 result{};
            GetAttribute<Matrix4>("transform", result);
            return result;
        }

        void SetTransform(const Matrix4 &transform) {
            SetAttribute<Matrix4>("transform", transform);
        }

        static std::vector<AttributeSpec> GetDefaultAttributes();

    protected:
        Xform() = default;

        Xform(const EntityDataHandle &dataHandle, Scene *scene)
                : Entity(dataHandle, scene) {}

    private:
        friend Scene;

    };


}

#endif //RBND_XFORM_H
