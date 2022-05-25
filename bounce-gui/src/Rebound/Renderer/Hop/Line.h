//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_RENDER_LINE_H
#define HOP_RENDER_LINE_H

#include "Item.h"


namespace Hop::DrawItems {

    class Line : public DrawItem {
    public:
        Line(std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<Material> material)
                : DrawItem(std::move(material)),
                  m_vertexArray(std::move(vertexArray)) {}


        inline uint32_t GetElementCount() const {
            return m_vertexArray->GetIndexBuffer()->GetCount();
        }

    };

}


#endif //HOP_LINE_H
