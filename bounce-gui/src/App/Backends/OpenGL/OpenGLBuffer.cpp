//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Bounce::Gui {

    /// == VertexBuffer ============================================================================

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    BufferLayout OpenGLVertexBuffer::GetLayout() const {
        return m_layout;
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout &layout) {
        m_layout = layout;
    }

    /// == IndexBuffer =============================================================================

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
            : m_count(count) {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t OpenGLIndexBuffer::GetCount() const {
        return m_count;
    }

}