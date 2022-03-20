//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_LINE_H
#define BOUNCE_GUI_LINE_H


#include "RenderItem.h"
#include "VertexArray.h"

namespace Bounce::Gui {

    class Line : public RenderItem {
    public:
        Line(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
                : RenderItem(std::move(material)),
                  m_vertexArray(std::move(vertexArray)) {}

        inline void Bind() const override { m_vertexArray->Bind(); }
        inline void Unbind() const override { m_vertexArray->Unbind(); }

        inline unsigned int GetElementCount() const {
            return m_vertexArray->GetIndexBuffer()->GetCount();
        }

        RENDER_ITEM_TYPE(Line);

    protected:
        std::shared_ptr<VertexArray> m_vertexArray;
    };

}


#endif //BOUNCE_GUI_LINE_H
