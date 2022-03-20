//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "Buffer.h"
#include "Renderer.h"

#include "App/Backends/OpenGL/OpenGLBuffer.h"

namespace Bounce::Gui {

    VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
        }

        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int size) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return new OpenGLIndexBuffer(indices, size);
        }

        return nullptr;
    }

}