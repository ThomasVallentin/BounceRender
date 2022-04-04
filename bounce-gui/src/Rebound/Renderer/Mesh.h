//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_MESH_H
#define RBND_MESH_H

#include "Item.h"
#include "VertexArray.h"

#include <memory>
#include <utility>


namespace Rebound::RenderItems {

    class Mesh : public RenderItem {
    public:
        Mesh(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
                : RenderItem(std::move(material)),
                  m_vertexArray(std::move(vertexArray)) {}

        inline void Bind() const override { m_vertexArray->Bind(); }
        inline void Unbind() const override { m_vertexArray->Unbind(); }

        inline uint32_t GetElementCount() const {
            return m_vertexArray->GetIndexBuffer()->GetCount();
        }

        RENDER_ITEM_TYPE(Mesh);

    protected:
        std::shared_ptr<VertexArray> m_vertexArray;
    };


}

#endif //RBND_MESH_H
