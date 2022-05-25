//
// Created by Thomas Vallentin on 21/03/2022.
//

#include "FrameBuffer.h"

#include "Rebound/Renderer/Hop/Backends/OpenGL/OpenGLFrameBuffer.h"
#include "RenderDelegate.h"

namespace Hop {

    std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec &spec) {
        switch (RenderDelegate::GetAPI()) {
            case RenderAPI::None: return nullptr;
            case RenderAPI::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
        }

        return nullptr;
    }
}

