//
// Created by Thomas Vallentin on 26/04/2022.
//

#ifndef RBND_RENDERDELEGATE_H
#define RBND_RENDERDELEGATE_H

#include "Rebound/Scene/Entity.h"

#include <vector>
#include <map>

namespace Rebound {

    class RenderScene;
    class RenderEntity;
    class Camera;

    class RenderDelegate {
    public:
        RenderDelegate() : m_scene(nullptr) {}
        explicit RenderDelegate(RenderScene *scene) : m_scene(scene) {}

        virtual bool Render(Camera *camera) = 0;

        virtual bool Pause() = 0;
        virtual bool Resume() = 0;

        virtual bool Stop() = 0;
        virtual bool Restart() = 0;

        virtual RenderEntity *CreateRenderEntity(const EntityDataHandle& handle) = 0;

    protected:
        RenderScene *m_scene;
    };

}

#endif //RBND_RENDERDELEGATE_H
