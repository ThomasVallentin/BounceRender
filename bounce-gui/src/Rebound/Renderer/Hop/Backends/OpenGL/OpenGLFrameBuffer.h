//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef HOP_OPENGLFRAMEBUFFER_H
#define HOP_OPENGLFRAMEBUFFER_H

#include "Rebound/Renderer/Hop/FrameBuffer.h"


namespace Hop {

    class OpenGLFrameBuffer : public FrameBuffer {
    public:
        explicit OpenGLFrameBuffer(const FrameBufferSpec &spec);

        void Resize(const uint32_t &width, const uint32_t &height) override;
        void Bind() const override;
        void Unbind() const override;

        uint32_t GetColorAttachmentID() const override;

        inline const FrameBufferSpec GetSpecifications() const override { return m_spec; }

    private:
        void Invalidate();

        uint32_t m_ID, m_colorAttachmentID, m_depthAttachmentID;

        FrameBufferSpec m_spec;
    };

}

#endif //HOP_OPENGLFRAMEBUFFER_H
