//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_RENDERITEM_H
#define RBND_RENDERITEM_H


#include <utility>

#include "Material.h"


namespace Rebound {

#define RENDER_ITEM_TYPE(type) static inline DrawType GetStaticType() { return DrawType::type; } \
                               inline DrawType GetType() const override { return GetStaticType(); }
    enum class DrawType {
        None = 0,
        Mesh = 1,
        Line = 2
    };

    class RenderItem {
    public:
        explicit RenderItem(std::shared_ptr<Material> material)
            : m_material(material), m_transformMatrix() {}
        ~RenderItem() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        inline float* GetTransform() { return m_transformMatrix; }
        std::shared_ptr<Material> GetMaterial() { return m_material; }

        virtual DrawType GetType() const = 0;

    protected:
        float m_transformMatrix[16];
        std::shared_ptr<Material> m_material;
    };


}


#endif //RBND_RENDERITEM_H
