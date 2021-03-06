//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLShader.h"

#include "glad/glad.h"
#include "Rebound/Core/Logging.h"

#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <vector>


namespace Hop {

    OpenGLShader::OpenGLShader(const char *vertexCode, const char *fragmentCode) {
        uint32_t vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexCode, nullptr);
        glCompileShader(vertexShader);

        GLint success = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        // If the vertex shader hasn't been successfully compiled,
        // getting the info log, print it and return
        if (success == GL_FALSE) {
            GLint logLength;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log(logLength);
            glGetShaderInfoLog(vertexShader, logLength, &logLength, log.data());
            RBND_ERROR("Could not compile vertex shader :\n%s\n", log.data());

            glDeleteShader(vertexShader);

            return;
        }

        uint32_t fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
        glCompileShader(fragmentShader);

        success = GL_FALSE;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        // If the fragment shader hasn't been successfully compiled,
        // getting the info log, print it and return
        if (success == GL_FALSE) {
            GLint logLength;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log(logLength);
            glGetShaderInfoLog(fragmentShader, logLength, &logLength, log.data());
            RBND_ERROR("Could not compile fragment shader :\n%s\n", log.data());

            glDeleteShader(fragmentShader);

            return;
        }

        // Vertex and fragment shader are loaded, creating a program and attaching them to it.
        m_programId = glCreateProgram();
        glAttachShader(m_programId, vertexShader);
        glAttachShader(m_programId, fragmentShader);

        // Link the program
        glLinkProgram(m_programId);

        success = GL_FALSE;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
        // If the shader program hasn't been successfully linked,
        // getting the info log, print it and return
        if (success == GL_FALSE) {
            GLint logLength;
            glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<GLchar> log(logLength);
            glGetProgramInfoLog(m_programId, logLength, &logLength, log.data());
            RBND_ERROR("Could not link shader : \n%s\n", log.data());

            glDeleteProgram(m_programId);

            return;
        }

        // Delete the shaders as they're linked into our program and are no longer necessary
        glDetachShader(m_programId, vertexShader);
        glDetachShader(m_programId, fragmentShader);
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_programId);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_programId);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string &name, const int &value) const {
        GLint location = glGetUniformLocation(m_programId, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::SetFloat(const std::string &name, const float &value) const {
        GLint location = glGetUniformLocation(m_programId, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &value) const {
        GLint location = glGetUniformLocation(m_programId, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) const {
        GLint location = glGetUniformLocation(m_programId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

}