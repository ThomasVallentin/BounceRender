//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "RenderLayer.h"

#include "App/Renderer/Renderer.h"
#include "App/Renderer/Mesh.h"

#include "App/Core/Logging.h"

#include "imgui.h"
#include "imgui_internal.h"

#include <memory>

namespace Bounce::Gui {

    RenderLayer::RenderLayer() {
    }

    void RenderLayer::OnAttach() {
        m_camera = std::make_shared<Camera>( 50.0f, 1280.0f / 720.0f, 0.1f, 10000.0f);

        // Vertical plane
        float vertices[4 * 3] {
                -0.5f, 0.0f, 0.0f,
                0.5f, 0.0f, 0.0f,
                0.5f, 1.0f, 0.0f,
                -0.5f, 1.0f, 0.0f
        };
        uint32_t indices[6]{0, 1, 2, 2, 3, 0};

        m_vertexArray = VertexArray::Create();
        m_vertexArray->Bind();

        auto vertexBuffer = VertexBuffer::Create(
                vertices,
                sizeof(vertices));
        vertexBuffer->SetLayout({
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
        uint32_t floorIndices[6]{0, 1, 2, 2, 3, 0};

        m_floorVA = VertexArray::Create();
        m_floorVA->Bind();

        auto floorVB = VertexBuffer::Create(
                floorVertices,
                sizeof(floorVertices));
        floorVB->SetLayout({
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

        FrameBufferSpec spec{1280, 720,
                             FrameBufferTextureFormat::RGBA8,
                             FrameBufferTextureFormat::Depth,
                             1};
        m_viewportFrameBuffer = FrameBuffer::Create(spec);
    }

    void RenderLayer::OnDetach() {
    }

    void RenderLayer::OnUpdate() {
        // Updating frame buffer size if the viewport size has changed
        const FrameBufferSpec spec = m_viewportFrameBuffer->GetSpecifications();
        if ((uint32_t) m_viewportWidth != spec.width || (uint32_t) m_viewportHeight != spec.height) {
            BNC_INFO("m_viewport : %d, %d", m_viewportWidth, m_viewportHeight);
            m_camera->SetViewportSize(m_viewportWidth, m_viewportHeight);
            m_viewportFrameBuffer->Resize((uint32_t) m_viewportWidth,
                                          (uint32_t) m_viewportHeight);
        }
        m_viewportFrameBuffer->Bind();

        // Sending items to the renderer
        // TODO(tvallentin): This needs to be extracted when the Scene system will come
        RenderItem* mesh = new Mesh(m_vertexArray, m_material);
        RenderItem* floorMesh = new Mesh(m_floorVA, m_material);

        Renderer::BeginScene(*m_camera);
        Renderer::Submit(mesh);
        Renderer::Submit(floorMesh);
        Renderer::EndScene();

        Renderer::Flush();

        m_viewportFrameBuffer->Unbind();
    }

    void RenderLayer::OnEvent(Event &event) {
        m_camera->OnEvent(event);
    }

    bool RenderLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        return false;
    }

    void RenderLayer::OnImGuiRender() {
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::Begin("MainDockSpace", nullptr, window_flags);

        // Pop the rounding, border & padding style vars set previously
        ImGui::PopStyleVar(3);

        // Submit the DockSpace
        ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMenuBar()) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4.0, 4.0f));

            if(ImGui::BeginMenu("File")) {

                if (ImGui::MenuItem("New")) { BNC_INFO("New scene !"); }
                if (ImGui::MenuItem("Open")) { BNC_INFO("Open scene !"); }
                if (ImGui::MenuItem("Save")) { BNC_INFO("Saving the current scene !"); }

                ImGui::EndMenu(); // File
            }

            if (ImGui::BeginMenu("View")) {

                if (ImGui::BeginMenu("Tool Windows")) {

                    ImGui::MenuItem("Scene Hierarchy", nullptr, &m_showSceneHierarchy);
                    ImGui::MenuItem("Property View", nullptr, &m_showPropertyView);

                    ImGui::EndMenu(); // UI Elements
                }

                ImGui::EndMenu(); // View
            }

            ImGui::EndMenuBar(); // Main menu bar
            ImGui::PopStyleVar();
        }

        ImGui::End(); // MainDockSpace

        // TODO(tvallentin): Extract the Scene hierarchy to a separate class
        if (m_showSceneHierarchy) {
            ImGui::Begin("Scene Hierarchy", &m_showSceneHierarchy);
            ImGui::End();
        }

        // TODO(tvallentin): Extract PropertyView to a separate class
        if (m_showPropertyView) {
            ImGui::Begin("Property View", &m_showPropertyView);

            const glm::vec3 &pos = m_camera->GetPosition();
            float position[3] { pos.x, pos.y, pos.z};
            const glm::vec3 &rot = glm::eulerAngles(m_camera->GetOrientation());
            float rotation[3]{glm::degrees(rot.x),
                              glm::degrees(rot.y),
                              glm::degrees(rot.z)};

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Translate");
            ImGui::SameLine(100);
            ImGui::DragFloat3("", position, 1.0f,
                              0.0f, 180.0f, "%.3f",
                              ImGuiSliderFlags_NoInput);

            ImGui::AlignTextToFramePadding();
            ImGui::Text("Rotate");
            ImGui::SameLine(100);
            ImGui::DragFloat3("", rotation, 1.0f,
                              0.0f, 180.0f, "%.3f",
                              ImGuiSliderFlags_NoInput);

            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse);
            // TODO(tvallentin): hide viewport tab bar

            if (ImGui::IsWindowFocused() || ImGui::IsWindowHovered()) {
                m_camera->OnUpdate();
            }

            // Update internal viewport size from the UI
            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            m_viewportWidth = viewportSize.x;
            m_viewportHeight = viewportSize.y;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
            if (ImGui::BeginMenuBar()) {

                RenderHints renderHints = Renderer::GetRenderHints();
                if (ImGui::BeginMenu("Display mode")) {

                    if (ImGui::MenuItem("Wireframe", nullptr,
                                        renderHints.displayMode == DisplayMode::Wireframe)) {
                        renderHints.displayMode = DisplayMode::Wireframe;
                        Renderer::SetRenderHints(renderHints);
                    }
                    if (ImGui::MenuItem("Shaded", nullptr,
                                        renderHints.displayMode == DisplayMode::SmoothShaded)) {
                        renderHints.displayMode = DisplayMode::SmoothShaded;
                        Renderer::SetRenderHints(renderHints);
                    }

                    ImGui::EndMenu(); // Display Mode
                }

                ImGui::PopStyleVar();
                ImGui::EndMenuBar();
            }

            uint64_t textureID = m_viewportFrameBuffer->GetColorAttachmentID();
            ImGui::Image(reinterpret_cast<void *>(textureID),
                         ImVec2(m_viewportWidth, m_viewportHeight),
                         ImVec2{0, 1}, ImVec2{1, 0});

            ImGui::End();
            ImGui::PopStyleVar();
        }

    }

}
