//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_OPENGLBUFFER_H
#define BOUNCE_GUI_OPENGLBUFFER_H

#include "App/Renderer/Buffer.h"

namespace Bounce::Gui {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, unsigned int size);
        ~OpenGLVertexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        BufferLayout GetLayout() const override;
        void SetLayout(const BufferLayout &layout) override;

    private:
        unsigned int m_id;
        BufferLayout m_layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
        ~OpenGLIndexBuffer() override;

        void Bind() const override;
        void Unbind() const override;

        unsigned int GetCount() const override;

    private:
        unsigned int m_id;
        unsigned int m_count;
    };

}

#endif //BOUNCE_GUI_OPENGLBUFFER_H
