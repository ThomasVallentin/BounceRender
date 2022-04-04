//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_VERTEXARRAY_H
#define RBND_VERTEXARRAY_H

#include "Buffer.h"

#include <memory>
namespace Rebound {

    class VertexArray {
    public:
        virtual ~VertexArray() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;
        virtual void SetIndexBuffer(std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

        static std::shared_ptr<VertexArray> Create();
    };

}

#endif //RBND_VERTEXARRAY_H
