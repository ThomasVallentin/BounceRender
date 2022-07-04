//
// Created by Thomas Vallentin on 02/07/2022.
//

#include "RenderView.h"
#include "Rebound/Renderer/Hop/RenderDelegate.h"

#include <OpenImageIO/imageio.h>
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>

namespace Rebound {
    RenderViewWidget::RenderViewWidget()
            : Widget("Render View") {

        SetWindowFlags(ImGuiWindowFlags_MenuBar);

        auto spec = new Hop::FrameBufferSpec{500, 500,
                                             Hop::FrameBufferTextureFormat::RGBA8,
                                             Hop::FrameBufferTextureFormat::Depth,
                                             1};
        m_frameBuffer = Hop::FrameBuffer::Create(spec);

        // Generate texture for the render view (it will receive the data from the Renderer)
        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderTextureId);

        // Initialize render quad material
        std::string vertexCode =  R"(
        #version 460 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec2 a_TexCoord;

        uniform mat4 u_viewProjMatrix;

        out vec3 v_Position;
        out vec2 v_TexCoord;

        void main()
        {
            v_Position = a_Position;
            v_TexCoord = a_TexCoord;
            gl_Position = u_viewProjMatrix * vec4(a_Position, 1.0);
        }
		)";
        std::string fragmentCode = R"(
        #version 460 core

        layout(location = 0) out vec4 outColor;

        uniform sampler2D u_renderTexture;

        in vec3 v_Position;
        in vec2 v_TexCoord;

        void main()
        {
            outColor = texture(u_renderTexture, v_TexCoord);
        }
        )";

        auto renderQuadShader = Hop::Shader::Create(vertexCode.c_str(), fragmentCode.c_str());
        m_renderQuadMaterial = std::make_shared<Hop::Material>(renderQuadShader);
    }

    void RenderViewWidget::UpdateFromRenderBuffer() {
        auto spec = m_renderDelegate->GetFrameBuffer()->GetSpecifications();

        m_renderQuad = Hop::VertexArray::Create();

        float vertices[] = { 0.5f * spec->width,  0.5f * spec->height,  0.0f, 1.0f, 0.0f,
                             0.5f * spec->width, -0.5f * spec->height,  0.0f, 1.0f, 1.0f,
                            -0.5f * spec->width, -0.5f * spec->height,  0.0f, 0.0f, 1.0f,
                            -0.5f * spec->width,  0.5f * spec->height,  0.0f, 0.0f, 0.0f};
        std::shared_ptr<Hop::VertexBuffer> vtxBuffer =
                Hop::VertexBuffer::Create(vertices, sizeof(vertices));
        vtxBuffer->SetLayout({{Hop::ShaderDataType::Float3, "a_Position"},
                              {Hop::ShaderDataType::Float2, "a_TexCoord"}});

        // Index Buffer
        uint32_t indices[] = {0, 1, 3, 1, 2, 3};
        std::shared_ptr<Hop::IndexBuffer> idxBuffer =
                Hop::IndexBuffer::Create(indices, sizeof(indices));

        m_renderQuad->AddVertexBuffer(vtxBuffer);
        m_renderQuad->SetIndexBuffer(idxBuffer);
    }

    std::shared_ptr<BncRenderDelegate> RenderViewWidget::GetRenderDelegate() const {
        return m_renderDelegate;
    }

    void RenderViewWidget::SetRenderDelegate(std::shared_ptr<BncRenderDelegate> renderDelegate) {
        m_renderDelegate = std::move(renderDelegate);
        UpdateFromRenderBuffer();
    }

    void RenderViewWidget::SetCamera(std::shared_ptr<Camera> camera) {
        m_camera = std::move(camera);
    }

    void RenderViewWidget::PreRender() {
        if (IsInteractive() && !m_renderDelegate->GetRenderScene()->IsUpToDate()) {
             Restart();
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    }

    void RenderViewWidget::UpdateFrameBuffer() {
        // Resize the OpenGL texture so that it fits the whole available region
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_frameBuffer->Resize(viewportSize.x, viewportSize.y);

        if (m_renderDelegate) {
            // TODO: This should not be implemented in OpenGL but with an extra layer of
            //  abstraction this will need to be refactored with Hop::RenderDelegate
            auto renderBuffer =
                    std::dynamic_pointer_cast<BncFrameBuffer>(m_renderDelegate->GetFrameBuffer());
            auto renderSpec = renderBuffer->GetSpecifications();

            // Transfer the data from the renderbuffer to the texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_renderTextureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTexImage2D(GL_TEXTURE_2D,
                         0, GL_RGB,
                         renderSpec->width, renderSpec->height,
                         0,
                         GL_RGB, GL_FLOAT,
                         renderBuffer->GetPixels().data());
        }
        m_frameBuffer->Bind();

        // TODO: Should be removed from here and moved to an Editor Camera Tool
        float vpAspectRatio = viewportSize.y / viewportSize.x;
        auto spec = m_renderDelegate->GetFrameBuffer()->GetSpecifications();
        glm::mat4 proj = glm::ortho((float) spec->width * -0.75,
                                    (float) spec->width * 0.75,
                                    (float) spec->height * 0.75 * -vpAspectRatio,
                                    (float) spec->height * 0.75 * vpAspectRatio);

        // Clear background
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Bind vertex buffer, bind material & set its uniforms, render the renderQuad
        m_renderQuad->Bind();
        m_renderQuadMaterial->Bind();
        m_renderQuadMaterial->GetShader()->SetInt("u_renderTexture", 0);
        m_renderQuadMaterial->GetShader()->SetMat4("u_viewProjMatrix", proj);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        m_renderQuadMaterial->Unbind();
        m_renderQuad->Unbind();

        m_frameBuffer->Unbind();
    }

    void RenderViewWidget::Render() {
        UpdateFrameBuffer();

        if (ImGui::BeginMenuBar()) {

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(4, 4));
            if (!m_renderDelegate->IsRunning()) {
                if (ImGui::Button("Start Render")) { Start(); }
            } else {
                if (ImGui::Button("Stop Render")) { Stop(); }
            }

            if (ImGui::BeginMenu("RenderSettings")) {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 2.0f));

                ImGui::Checkbox("Interactive render", &m_interactive);

                auto sharedData = dynamic_cast<BncRenderSharedData*>(m_renderDelegate->GetSharedData());
                auto renderSettings = sharedData->GetRenderSettings();

                int samples = (int) renderSettings->sampleCount;
                ImGui::DragInt("Samples", &samples, 1.0f, 1.0f, 1024.0f);
                renderSettings->sampleCount = samples;

                ImGui::EndMenu();
                ImGui::PopStyleVar();
            }
            ImGui::PopStyleVar();

            if (m_renderDelegate->IsRunning()) {
                std::string text = "Rendering in progress...";
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(text.c_str()).x
                                     - ImGui::GetScrollX() - 2 * ImGui::GetStyle().ItemSpacing.x);
                ImGui::Text("%s", text.c_str());
            }

            ImGui::EndMenuBar();
        }

        // Render ImGui elements
        uint64_t textureID = m_frameBuffer->GetColorAttachmentID();
        ImGui::Image(reinterpret_cast<void *>(textureID),
                     ImGui::GetContentRegionAvail(),
                     ImVec2{0, 1},
                     ImVec2{1, 0});
    }

    void RenderViewWidget::PostRender() {
        ImGui::PopStyleVar();
    }

    void RenderViewWidget::Start() const {
        if (!m_renderDelegate) {
            RBND_WARNING("Could not start render since there is no "
                         "RenderDelegate attached to the RenderView");
            return;
        }
        if (!m_camera) {
            RBND_WARNING("Could not start render since there is no "
                         "Camera attached to the RenderView");
            return;
        }

        m_renderDelegate->GetRenderScene()->Sync();
        m_renderDelegate->Render(m_camera.get());
    }

    void RenderViewWidget::Stop() const {
        m_renderDelegate->Stop();
    }

    void RenderViewWidget::Restart() const {
        Stop();
        Start();
    }

    bool RenderViewWidget::IsInteractive() const {
        return m_interactive;
    }

}