//
// Created by Thomas Vallentin on 16/03/2022.
//

#ifndef HOP_OPENGLSHADER_H
#define HOP_OPENGLSHADER_H

#include "Rebound/Renderer/Hop/Shader.h"


namespace Hop {

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader() : m_programId(0) {}
        OpenGLShader(const char* vertexCode, const char* fragmentCode);
        ~OpenGLShader();

        void Bind() const override;
        void Unbind() const override;
        inline bool IsValid() const override { return (m_programId != 0); }

        void SetInt(const std::string &name, const int &value) const override;
        void SetFloat(const std::string &name, const float &value) const override;
        void SetFloat3(const std::string &name, const glm::vec3 &value) const override;
        void SetMat4(const std::string &name, const glm::mat4 &value) const override;

    private:
        uint32_t m_programId;

    };

}
#endif //HOP_OPENGLSHADER_H
