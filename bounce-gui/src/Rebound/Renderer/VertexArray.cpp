//
// Created by Thomas Vallentin on 19/03/2022.
//


#include "VertexArray.h"
#include "Renderer.h"

#include "Rebound/Backends/OpenGL/OpenGLVertexArray.h"

namespace Rebound {

    std::shared_ptr<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None: return nullptr;
            case RenderAPI::OpenGL: return std::make_shared<OpenGLVertexArray>();
        }

        return nullptr;
    }
}

