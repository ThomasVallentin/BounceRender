//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_MATERIAL_H
#define BOUNCE_GUI_MATERIAL_H

#include "Shader.h"

#include <memory>

namespace Bounce::Gui {

    class Material {
    public:
        explicit Material(std::shared_ptr<Shader> shader)
                : m_shader(std::move(shader)) {}

        inline void Bind() const {
            m_shader->Bind();
            SetUniforms();
        }
        inline void Unbind() const {
            m_shader->Unbind();
        }
        inline void SetUniforms() const {}

    private:
        std::shared_ptr<Shader> m_shader;
    };

}


#endif //BOUNCE_GUI_MATERIAL_H
