//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef HOP_OPENGLFRAMEBUFFER_H
#define HOP_OPENGLFRAMEBUFFER_H

#include "Rebound/Renderer/Hop/FrameBuffer.h"


namespace Hop {

    class OpenGLFrameBuffer : public FrameBuffer {
        public:
            explicit OpenGLFrameBuffer(Rebound::FrameBufferSpec *spec);
            ~OpenGLFrameBuffer() override;

            void Resize(const uint32_t &width, const uint32_t &height) override;

            void Bind() const;
            void Unbind() const;

            uint32_t GetColorAttachmentID() const override;

        private:
            void Invalidate();

            uint32_t m_ID, m_colorAttachmentID, m_depthAttachmentID;
        };

}

#endif //HOP_OPENGLFRAMEBUFFER_H
