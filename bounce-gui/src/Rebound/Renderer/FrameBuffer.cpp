//
// Created by Thomas Vallentin on 21/03/2022.
//

#include "FrameBuffer.h"

#include "Rebound/Backends/OpenGL/OpenGLFrameBuffer.h"
#include "Renderer.h"

namespace Rebound {

    std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpec &spec) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None: return nullptr;
            case RenderAPI::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
        }

        return nullptr;
    }
}

