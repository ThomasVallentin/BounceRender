//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_MATERIAL_H
#define HOP_MATERIAL_H

#include "Shader.h"

#include "Rebound/Renderer/Material.h"

#include <memory>

namespace Hop {

    class Material : public Rebound::Material {
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

        inline std::shared_ptr<Shader> GetShader() const { return m_shader; }
        inline void SetUniforms() const {}

    private:
        std::shared_ptr<Shader> m_shader;
    };

}


#endif //HOP_MATERIAL_H
