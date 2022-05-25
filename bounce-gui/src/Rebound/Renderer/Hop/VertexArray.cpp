//
// Created by Thomas Vallentin on 19/03/2022.
//


#include "VertexArray.h"
#include "RenderDelegate.h"

#include "Rebound/Renderer/Hop/Backends/OpenGL/OpenGLVertexArray.h"

namespace Hop {

    std::shared_ptr<VertexArray> VertexArray::Create() {
        switch (RenderDelegate::GetAPI()) {
            case RenderAPI::None: return nullptr;
            case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexArray>();
        }

        return nullptr;
    }
}

