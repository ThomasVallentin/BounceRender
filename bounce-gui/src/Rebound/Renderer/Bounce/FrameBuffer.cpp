//
// Created by Thomas Vallentin on 02/07/2022.
//

#include "FrameBuffer.h"


namespace Rebound {

    BncFrameBuffer::BncFrameBuffer(FrameBufferSpec *spec)
            : FrameBuffer(spec) {
        m_pixels = std::vector<float>(spec->width * spec->height * 3);
    }

    std::shared_ptr<FrameBuffer> BncFrameBuffer::Create(FrameBufferSpec *spec) {
        return std::make_shared<BncFrameBuffer>(spec);
    }

    void BncFrameBuffer::Resize(const uint32_t &width, const uint32_t &height) {
        FrameBufferSpec *spec = GetSpecifications();
        spec->width = width;
        spec->height = height;
        m_pixels = std::vector<float>(spec->width * spec->height * 3);
    }

    std::vector<float> &BncFrameBuffer::GetPixels() {
        return m_pixels;
    }

}
