//
// Created by Thomas Vallentin on 16/03/2022.
//


#include "Shader.h"
#include "Renderer.h"

#include "Rebound/Backends/OpenGL/OpenGLShader.h"

namespace Rebound {

    std::shared_ptr<Shader> Shader::Create(const char *vertexCode, const char *fragmentCode) {
        switch (Renderer::GetAPI()) {
            case RenderAPI::None:    return nullptr;
            case RenderAPI::OpenGL:  return std::make_shared<OpenGLShader>(vertexCode, fragmentCode);
        }

        return nullptr;
    }

    std::shared_ptr<Shader> Shader::Load(const char *vertexPath, const char *fragmentPath) {
        {
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                // open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // close file handlers
                vShaderFile.close();
                fShaderFile.close();
                // convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch (std::ifstream::failure &e) {
                fprintf(stderr,
                        "# Error:\n%s\nSomething went wrong trying to read shader file",
                        e.what());

                return nullptr;
            }
            const char *vShaderCode = vertexCode.c_str();
            const char *fShaderCode = fragmentCode.c_str();

            return Create(vShaderCode, fShaderCode);
        }
    }
}
