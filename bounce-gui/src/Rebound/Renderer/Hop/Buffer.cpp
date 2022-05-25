//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "Buffer.h"
#include "RenderDelegate.h"

#include "Rebound/Renderer/Hop/Backends/OpenGL/OpenGLBuffer.h"

namespace Hop {

    std::shared_ptr<VertexBuffer>  VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (RenderDelegate::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
        switch (RenderDelegate::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, size);
        }

        return nullptr;
    }

}