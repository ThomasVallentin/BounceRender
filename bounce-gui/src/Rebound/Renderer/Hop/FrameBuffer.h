//
// Created by Thomas Vallentin on 05/06/2022.
//

#ifndef HOP_FRAMEBUFFER_H
#define HOP_FRAMEBUFFER_H

#include "Rebound/Renderer/FrameBuffer.h"


namespace Hop {

    enum class FrameBufferTextureFormat {
        None = 0,

        // Color
        RGBA8,

        // Depth & stencil
        DEPTH24STENCIL8,

        // Default
        Depth = DEPTH24STENCIL8
    };

    struct FrameBufferSpec : public Rebound::FrameBufferSpec {
        FrameBufferSpec(const uint32_t &width,
                        const uint32_t &height,
                        const FrameBufferTextureFormat &colorFmt,
                        const FrameBufferTextureFormat &depthFmt,
                        const uint32_t &samples) :
                Rebound::FrameBufferSpec(width, height),
                colorFormat(colorFmt),
                depthFormat(depthFmt),
                samples(samples) {}

        FrameBufferTextureFormat colorFormat = FrameBufferTextureFormat::RGBA8;
        FrameBufferTextureFormat depthFormat = FrameBufferTextureFormat::Depth;
        uint32_t samples = 1;
    };

    class FrameBuffer : public Rebound::FrameBuffer {
    public:
        explicit FrameBuffer(Rebound::FrameBufferSpec* spec) : Rebound::FrameBuffer(spec) {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetColorAttachmentID() const = 0;

        static std::shared_ptr<FrameBuffer> Create(FrameBufferSpec *spec);
    };

}

#endif //HOP_FRAMEBUFFER_H
