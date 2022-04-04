//
// Created by Thomas Vallentin on 04/04/2022.
//

#ifndef RBND_RENDERSCENE_H
#define RBND_RENDERSCENE_H

#include "Item.h"

#include "Rebound/Scene/Entity.h"


namespace Rebound {

    class RenderScene {
    public:
        RenderScene() = default;

        void AddEntity(const Entity* entity);
        void Update();

        void Submit();

    private:
        std::unordered_map<EntityDataHandle, RenderItem*> m_items;
    };

}

#endif //RBND_RENDERSCENE_H
