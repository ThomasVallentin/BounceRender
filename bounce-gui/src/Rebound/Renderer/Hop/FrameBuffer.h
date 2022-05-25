//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef HOP_FRAMEBUFFER_H
#define HOP_FRAMEBUFFER_H

#include <memory>
#include <vector>

namespace Hop {

    enum class FrameBufferTextureFormat {
        None = 0,

        // Color
        RGBA8,

        // Depth & stencil
        DEPTH24STENCIL8,

        // Default depth
        Depth = DEPTH24STENCIL8
    };

    struct FrameBufferSpec {
        uint32_t width = 0, height = 0;
        FrameBufferTextureFormat colorFormat;
        FrameBufferTextureFormat depthFormat;
        uint32_t samples = 1;
    };

    class FrameBuffer {
    public:
        virtual ~FrameBuffer() = default;

        virtual void Resize(const uint32_t &width, const uint32_t &height) = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetColorAttachmentID() const = 0;
        virtual const FrameBufferSpec GetSpecifications() const = 0;
        static std::shared_ptr<FrameBuffer> Create(const FrameBufferSpec &spec);
    };

}

#endif //HOP_FRAMEBUFFER_H
