//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "Buffer.h"
#include "Renderer.h"

#include "App/Backends/OpenGL/OpenGLBuffer.h"

namespace Bounce::Gui {

    std::shared_ptr<VertexBuffer>  VertexBuffer::Create(float* vertices, unsigned int size) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int size) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, size);
        }

        return nullptr;
    }

}