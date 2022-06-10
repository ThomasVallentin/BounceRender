//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_DRAWITEW_H
#define RBND_DRAWITEW_H


#include "Material.h"
#include "RenderScene.h"

#include <utility>
#include <memory>


namespace Rebound {

    class RenderEntity;

    /// DrawItems are meant to be consumed by the renderer. Their are the smallest object
    /// represented by the Renderer API as they represent a portion of a RenderEntity
    /// with a single material assigned
    /// The Material implementation have to be done for each delegate since it is dependent on
    /// the renderer.
    /// In some cases, the DrawItem implementation can be totally skipped,
    /// if the renderer already have a similar concept that can be used instead.
    class DrawItem {
    public:
        explicit DrawItem(const MaterialHandle& materialHandle) :
                m_materialHandle(materialHandle) {}
        virtual ~DrawItem() = default;

        MaterialHandle GetMaterialHandle() const { return m_materialHandle; }

    private:
        bool m_visible = true;
        MaterialHandle m_materialHandle;
    };

}

#endif //RBND_DRAWITEW_H
