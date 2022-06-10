//
// Created by Thomas Vallentin on 05/06/2022.
//


#include "FrameBuffer.h"
#include "RenderDelegate.h"

#include "Rebound/Renderer/Hop/Backends/OpenGL/OpenGLFrameBuffer.h"


namespace Hop {

    std::shared_ptr<FrameBuffer> FrameBuffer::Create(FrameBufferSpec *spec) {
        switch (RenderDelegate::GetAPI()) {
            case RenderAPI::None: return nullptr;
            case RenderAPI::OpenGL: return std::make_shared<OpenGLFrameBuffer>(spec);
        }

        return nullptr;
    }

}

