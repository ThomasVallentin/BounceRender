//
// Created by Thomas Vallentin on 02/07/2022.
//

#ifndef BOUNCE_FRAMEBUFFER_H
#define BOUNCE_FRAMEBUFFER_H

#include "Rebound/Renderer/FrameBuffer.h"

namespace Rebound {

    class BncFrameBuffer : public FrameBuffer {
    public:
        explicit BncFrameBuffer(FrameBufferSpec* spec);

        void Resize(const uint32_t &width, const uint32_t &height) override;
        std::vector<float> &GetPixels();

        static std::shared_ptr<FrameBuffer> Create(FrameBufferSpec *spec);

    private:
        std::vector<float> m_pixels;
    };

}

#endif //BOUNCE_FRAMEBUFFER_H
