//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>


namespace Hop {

    static GLint GetShaderTypeDimension(const ShaderDataType &type) {
        switch (type) {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Mat3:    return 9;
            case ShaderDataType::Mat4:    return 16;
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;
            case ShaderDataType::Bool:    return 1;
            case ShaderDataType::None:    return 0;
        }

        return 0;
    }
    static GLenum ShaderTypeToOpenGL(const ShaderDataType &type) {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:    return GL_FLOAT;

            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:    return GL_INT;

            case ShaderDataType::Bool:    return GL_BOOL;
        }

        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &m_id);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_id);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_id);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer> &vertexBuffer) {
        // Bind the vertex array to edit its data
        glBindVertexArray(m_id);
        vertexBuffer->Bind();

        // Looping over all the elements of the vertex buffer layout
        // to bind their data to the vertex array
        const BufferLayout &layout = vertexBuffer->GetLayout();
        uint32_t index = 0;
        for (const auto &element : vertexBuffer->GetLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  GetShaderTypeDimension(element.type),
                                  ShaderTypeToOpenGL(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void*)element.offset);
            index++;
        }

        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> &indexBuffer) {
        // Binding the vertex array and the index array to bind the to together
        glBindVertexArray(m_id);
        indexBuffer->Bind();

        m_indexBuffer = indexBuffer;
    }

}
