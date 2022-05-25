//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_DRAWITEW_H
#define HOP_DRAWITEW_H


#include <utility>

#include "Material.h"
#include "VertexArray.h"


namespace Hop {

    enum class DrawType {
        None = 0,
        Mesh = 1,
        Line = 2
    };

    class DrawItem {
    public:
        DrawItem(std::shared_ptr<VertexArray> vertexArray,
                 std::shared_ptr<Material> material,
                 const DrawType &type) :
                m_vertexArray(std::move(vertexArray)),
                m_material(std::move(material)),
                m_drawType(type),
                m_transformMatrix() {}

        ~DrawItem() = default;

        inline virtual void Bind() const { m_vertexArray->Bind(); }
        inline virtual void Unbind() const { m_vertexArray->Unbind(); }

        inline float* GetTransform() { return m_transformMatrix; }
        std::shared_ptr<Material> GetMaterial() { return m_material; }
        inline uint32_t GetElementCount() const {
            return m_vertexArray->GetIndexBuffer()->GetCount();
        }

        inline DrawType GetType() const { return m_drawType; }

    protected:
        float m_transformMatrix[16];
        std::shared_ptr<Material> m_material;
        std::shared_ptr<VertexArray> m_vertexArray;

        DrawType m_drawType;
    };

}


#endif //HOP_DRAWITEW_H
