//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_OPENGLVERTEXARRAY_H
#define BOUNCE_GUI_OPENGLVERTEXARRAY_H


#include "App/Renderer/VertexArray.h"

namespace Bounce::Gui {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        void SetIndexBuffer(std::shared_ptr<IndexBuffer> &indexBuffer) override;

        inline const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override {
            return m_vertexBuffers;
        };
        inline const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override {
            return m_indexBuffer;
        };


    private:
        uint32_t m_id;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };

}


#endif //BOUNCE_GUI_OPENGLVERTEXARRAY_H
