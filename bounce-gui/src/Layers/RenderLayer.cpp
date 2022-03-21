//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "RenderLayer.h"

#include "App/Renderer/Renderer.h"
#include "App/Renderer/Mesh.h"

#include "App/Core/Logging.h"
#include "App/Renderer/Line.h"

#include <memory>

#include <glad/glad.h>

namespace Bounce::Gui {

    RenderLayer::RenderLayer() {
        m_camera = std::make_shared<Camera>( 50.0f, 1280.0f / 720.0f, 0.1f, 10000.0f);

        // Vertical plane
        float vertices[4 * 3] {
                -0.5f, 0.0f, 0.0f,
                0.5f, 0.0f, 0.0f,
                0.5f, 1.0f, 0.0f,
                -0.5f, 1.0f, 0.0f
        };
        unsigned int indices[6]{0, 1, 2, 2, 3, 0};

        m_vertexArray = VertexArray::Create();
        m_vertexArray->Bind();

        auto vertexBuffer = VertexBuffer::Create(
                vertices,
                sizeof(vertices));
        vertexBuffer->SetLayout( {
                {ShaderDataType::Float3, "a_Position"}
        });

        auto indexBuffer = IndexBuffer::Create(
                indices,
                sizeof(indices));

        m_vertexArray->AddVertexBuffer(vertexBuffer);
        m_vertexArray->SetIndexBuffer(indexBuffer);

        // Floor
        float floorVertices[4 * 3] {
                -1.0f, 0.0f, -1.0f,
                1.0f,  0.0f, -1.0f,
                1.0f,  0.0f, 1.0f,
                -1.0f, 0.0f, 1.0f
        };
        unsigned int floorIndices[6]{0, 1, 2, 2, 3, 0};

        m_floorVA = VertexArray::Create();
        m_floorVA->Bind();

        auto floorVB = VertexBuffer::Create(
                floorVertices,
                sizeof(floorVertices));
        floorVB->SetLayout( {
                {ShaderDataType::Float3, "a_Position"}
        });

        auto floorIB = IndexBuffer::Create(
                floorIndices,
                sizeof(floorIndices));

        m_floorVA->AddVertexBuffer(floorVB);
        m_floorVA->SetIndexBuffer(floorIB);

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

        std::shared_ptr<Shader> shader = Shader::Create(vertexCode.c_str(),
                                                        fragmentCode.c_str());
        m_material = std::make_shared<Material>(shader);
    }

    void RenderLayer::OnAttach() {
    }

    void RenderLayer::OnDetach() {
    }

    void RenderLayer::OnUpdate() {
        m_camera->OnUpdate();

        RenderItem* mesh = new Mesh(m_vertexArray, m_material);
        RenderItem* floorMesh = new Mesh(m_floorVA, m_material);

        Renderer::BeginScene(*m_camera);
        Renderer::Submit(mesh);
        Renderer::Submit(floorMesh);
        Renderer::EndScene();

        Renderer::Flush();
    }

    void RenderLayer::OnEvent(Event &event) {
        m_camera->OnEvent(event);

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(RenderLayer::OnWindowResizeEvent));
    }

    bool RenderLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        BNC_DEBUG("Resize event %d %d", event.GetWidth(), event.GetHeight());

        m_camera->SetViewportSize(event.GetWidth(), event.GetHeight());
        glViewport(0, 0, event.GetWidth(), event.GetHeight());

        return false;
    }

}
