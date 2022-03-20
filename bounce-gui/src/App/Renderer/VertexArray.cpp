//
// Created by Thomas Vallentin on 19/03/2022.
//


#include "VertexArray.h"
#include "Renderer.h"

#include "App/Backends/OpenGL/OpenGLVertexArray.h"

namespace Bounce::Gui {

    VertexArray *VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RenderAPI::OpenGL: return new OpenGLVertexArray();
            case RenderAPI::None: return nullptr;
        }

        return nullptr;
    }
}

