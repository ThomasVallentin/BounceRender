//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_OPENGLBUFFER_H
#define BOUNCE_GUI_OPENGLBUFFER_H

#include "App/Renderer/Buffer.h"

namespace Bounce::Gui {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        BufferLayout GetLayout() const override;
        void SetLayout(const BufferLayout &layout) override;

    private:
        uint32_t m_id;
        BufferLayout m_layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        uint32_t GetCount() const override;

    private:
        uint32_t m_id;
        uint32_t m_count;
    };

}

#endif //BOUNCE_GUI_OPENGLBUFFER_H
