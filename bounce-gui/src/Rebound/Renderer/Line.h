//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_LINE_H
#define RBND_LINE_H


#include "Item.h"
#include "VertexArray.h"

namespace Rebound {

    class Line : public RenderItem {
    public:
        Line(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
                : RenderItem(std::move(material)),
                  m_vertexArray(std::move(vertexArray)) {}

        inline void Bind() const override { m_vertexArray->Bind(); }
        inline void Unbind() const override { m_vertexArray->Unbind(); }

        inline uint32_t GetElementCount() const {
            return m_vertexArray->GetIndexBuffer()->GetCount();
        }

        RENDER_ITEM_TYPE(Line);

    protected:
        std::shared_ptr<VertexArray> m_vertexArray;
    };

}


#endif //RBND_LINE_H
