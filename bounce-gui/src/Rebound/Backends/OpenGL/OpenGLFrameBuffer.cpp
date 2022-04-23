//
// Created by Thomas Vallentin on 21/03/2022.
//

#include "OpenGLFrameBuffer.h"
#include "Rebound/Core/Logging.h"

#include <glad/glad.h>

namespace Rebound {

    GLenum FrameBufferTextureFormatToOpenGL(const FrameBufferTextureFormat &format) {
        switch (format) {

            case FrameBufferTextureFormat::None: return 0;
            case FrameBufferTextureFormat::RGBA8: return GL_RGBA8;
            case FrameBufferTextureFormat::DEPTH24STENCIL8: return GL_DEPTH24_STENCIL8;
        }
        return 0;
    }

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpec &spec)
            : m_spec(spec) {
        Invalidate();
    }

    void OpenGLFrameBuffer::Resize(const uint32_t &width, const uint32_t &height) {
        m_spec.width = width;
        m_spec.height = height;

        Invalidate();
    }

    void OpenGLFrameBuffer::Bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
        glViewport(0, 0, (int) m_spec.width, (int) m_spec.height);
    }
    void OpenGLFrameBuffer::Unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    uint32_t OpenGLFrameBuffer::GetColorAttachmentID() const {
        return m_colorAttachmentID;
    }

    void OpenGLFrameBuffer::Invalidate() {
        if (m_ID) {
            // Deleting the framebuffer to recreate it
            glDeleteFramebuffers(1, &m_ID);
            glDeleteTextures(1, &m_colorAttachmentID);
            glDeleteTextures(1, &m_depthAttachmentID);

            m_colorAttachmentID = 0;
            m_depthAttachmentID = 0;
        }

        // Create framebuffer
        glCreateFramebuffers(1, &m_ID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

        // Create color attachment texture
        if (m_spec.colorFormat != FrameBufferTextureFormat::None) {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachmentID);
            glBindTexture(GL_TEXTURE_2D, m_colorAttachmentID);

            glTexImage2D(GL_TEXTURE_2D, 0, FrameBufferTextureFormatToOpenGL(m_spec.colorFormat),
                         (int) m_spec.width, (int) m_spec.height,
                         0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                                   m_colorAttachmentID, 0);
        } else {
            glDrawBuffer(GL_NONE);
        }

        if (m_spec.depthFormat != FrameBufferTextureFormat::None) {
            // Create depth attachment texture
            glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachmentID);
            glBindTexture(GL_TEXTURE_2D, m_depthAttachmentID);

            glTexStorage2D(GL_TEXTURE_2D, 1, FrameBufferTextureFormatToOpenGL(m_spec.depthFormat),
                           (int) m_spec.width, (int) m_spec.height);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D,
                                   m_depthAttachmentID, 0);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
