//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "RenderDelegate.h"

#include <memory>

#include "Mesh.h"
#include "Line.h"

#include "Rebound/Renderer/Hop/Backends/OpenGL/OpenGLRenderer.h"
#include "Rebound/Renderer/RenderScene.h"
#include "Rebound/Renderer/Camera.h"

#include "Rebound/Scene/Entities/Mesh.h"
#include "Rebound/Scene/Entities/Line.h"


namespace Hop {

    // TODO: Move this so that it is initialized with the Application based on hardware, software
    //  and user preferences.
    RenderAPI RenderDelegate::s_renderApi = RenderAPI::OpenGL;

    RenderDelegate::RenderDelegate() :
            Rebound::RenderDelegate(nullptr),
            m_renderHints({DisplayMode::SmoothShaded,
                           LightingMode::DefaultLighting}) {
        Initialize();
    }

    RenderDelegate::RenderDelegate(Rebound::RenderScene *scene) :
            Rebound::RenderDelegate(scene),
            m_renderHints({DisplayMode::SmoothShaded,
            LightingMode::DefaultLighting}) {
        Initialize();
    }

    void RenderDelegate::Initialize() {
        std::string vertexCode =  R"(
        #version 460 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 u_viewProjMatrix;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = u_viewProjMatrix * vec4(a_Position, 1.0);
        }
		)";
        std::string fragmentCode = R"(
        #version 460 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
        }
        )";

        std::shared_ptr<Shader> defaultShader = Shader::Create(vertexCode.c_str(),
                                                               fragmentCode.c_str());
        auto material = std::make_shared<Material>(defaultShader);

        SetDefaultMaterial(std::dynamic_pointer_cast<Rebound::Material>(material));
    }

    bool RenderDelegate::Render(Rebound::Camera *camera) {
        auto frameBuffer = std::dynamic_pointer_cast<FrameBuffer>(GetFrameBuffer());

        // TODO: Should be extracted to be bale to render vertex arrays using the correct RenderAPI
        //  without having to go through the whole RenderDelegate process
        frameBuffer->Bind();
        switch (GetAPI()) {
            case RenderAPI::None:    break;  // TODO: Add warning
            case RenderAPI::OpenGL:  OpenGLRenderer::Render(this, camera); break;
        }
        frameBuffer->Unbind();

        return true;
    }

    Rebound::RenderEntity *
    RenderDelegate::CreateRenderEntity(const Rebound::EntityDataHandle &handle) {
        auto entity = GetRenderScene()->GetEntity(handle);

        if (entity.IsA<Rebound::Mesh>()) {
            // TODO: Since we don't have a proper Material system in the scene,
            //  we pass an empty handle. The renderer will then use the delegate's default material
            //  This should be replaced by passing the mesh's assignation data instead.
            return new RenderMesh(entity, 0);
        }
        else if (entity.IsA<Rebound::Line>()) {
            // TODO: Since we don't have a proper Material system in the scene,
            //  we pass an empty handle. The renderer will then use the delegate's default material
            //  This should be replaced by passing the mesh's assignation data instead.
            return new RenderLine(entity, 0);
        }

        return nullptr;
    }

    std::shared_ptr<Rebound::FrameBuffer>
    RenderDelegate::CreateFrameBuffer(Rebound::FrameBufferSpec *spec) const {
        return FrameBuffer::Create(dynamic_cast<FrameBufferSpec *>(spec));
    }

    std::shared_ptr<Rebound::Material> RenderDelegate::CreateMaterial(const Rebound::EntityDataHandle &handle) {
        // TODO: Implement this
        return nullptr;
    }

}
