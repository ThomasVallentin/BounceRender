//
// Created by Thomas Vallentin on 16/03/2022.
//

#ifndef HOP_SHADER_H
#define HOP_SHADER_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace Hop {

    class Shader
    {
    public:
        Shader() = default;
        Shader(const char* vertexCode, const char* fragmentCode) {}
        ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual bool IsValid() const = 0;

        virtual void SetFloat(const std::string &name, const float &value) const = 0;
        virtual void SetFloat3(const std::string &name, const glm::vec3 &value) const = 0;
        virtual void SetMat4(const std::string &name, const glm::mat4 &value) const = 0;

        static std::shared_ptr<Shader> Create(const char* vertexCode, const char* fragmentCode);
        static std::shared_ptr<Shader> Load(const char *vertexPath, const char *fragmentPath);

    };

}

#endif //HOP_SHADER_H
