//
// Created by Thomas Vallentin on 16/03/2022.
//

#ifndef BOUNCE_GUI_SHADER_H
#define BOUNCE_GUI_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Bounce::Gui {

    class Shader
    {
    public:
        Shader() = default;
        Shader(const char* vertexCode, const char* fragmentCode) {}
        ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual bool IsValid() const = 0;

        static Shader* Create(const char* vertexCode, const char* fragmentCode);
        static Shader* Load(const char *vertexPath, const char *fragmentPath);
    };

}

#endif //BOUNCE_GUI_SHADER_H
