//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef RBND_FRAMEBUFFER_H
#define RBND_FRAMEBUFFER_H

#include <memory>
#include <vector>


namespace Rebound {

    // TODO : This has been copied directly from the GPU / Realtime renderer implementation,
    //        it should be reworked so that the concepts are a bit more agnostic.

    struct FrameBufferSpec {
        FrameBufferSpec(const uint32_t &width, const uint32_t &height) :
                width(width),
                height(height) {}

        virtual ~FrameBufferSpec() = default;

        uint32_t width = 0, height = 0;
    };

    class FrameBuffer {
    public:
        FrameBuffer(FrameBufferSpec *spec) : m_spec(spec) {}
        virtual ~FrameBuffer() = default;

        virtual void Resize(const uint32_t &width, const uint32_t &height) = 0;

        virtual uint32_t GetColorAttachmentID() const = 0;
        inline FrameBufferSpec* GetSpecifications() const { return m_spec; }

    private:
        FrameBufferSpec *m_spec;
    };

}

#endif //RBND_FRAMEBUFFER_H
