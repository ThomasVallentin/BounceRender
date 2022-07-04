//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "MainLayer.h"

#include "Rebound/Renderer/Hop/RenderDelegate.h"

#include "Rebound/Scene/Entity.h"

#include "Rebound/Core/Logging.h"

#include "imgui.h"
#include "imgui_internal.h"

#include <memory>


namespace Rebound {

    // TODO: Should be reworked and be integrated in the viewport widget
    class CameraObserver : public Observer {
    public:
        CameraObserver(RenderViewWidget* renderView)
                : m_renderView(renderView) {}

        void Notified(Notice *notice) override {
            if  (m_renderView->IsInteractive())
                m_renderView->Restart();
        }

    private:
        RenderViewWidget* m_renderView;
    };

    MainLayer::MainLayer() = default;

    void MainLayer::OnAttach() {
        m_camera = std::make_shared<Camera>( 50.0f, 1280.0f / 720.0f, 0.1f, 10000.0f);

        // Create empty scene
        // TODO: Open a scene on disk if an argument is passed to the executable
        auto newScene = Scene::New();
        m_scene.reset(newScene);

        // Configure the scene hierarchy widget
        m_sceneHierarchyWid.SetScene(m_scene);

        // Configure the viewport
        m_vpRenderDelegate = std::make_shared<Hop::RenderDelegate>();
        m_vpRenderDelegate->SetRenderScene(new RenderScene(m_vpRenderDelegate.get()));
        auto spec = new Hop::FrameBufferSpec{1280, 720,
                                             Hop::FrameBufferTextureFormat::RGBA8,
                                             Hop::FrameBufferTextureFormat::Depth,
                                             1};
        m_vpRenderDelegate->SetFrameBuffer(m_vpRenderDelegate->CreateFrameBuffer(spec));

        // Configure the RenderView
        auto rdRenderDelegate = std::make_shared<BncRenderDelegate>();
        rdRenderDelegate->SetRenderScene(new RenderScene(rdRenderDelegate.get()));
        rdRenderDelegate->SetFrameBuffer(
                rdRenderDelegate->CreateFrameBuffer(new FrameBufferSpec{500, 500}));
        m_renderView.SetRenderDelegate(rdRenderDelegate);
        m_renderView.SetCamera(m_camera);

        // Connect the camera to a render invalidation
        m_camObserver = new CameraObserver(&m_renderView);
        Notifier<Camera*>::RegisterObserver(m_camera.get(), m_camObserver);
    }

    void MainLayer::OnDetach() {
    }


    void MainLayer::OnUpdate() {
        // Updating frame buffer size if the viewport size has changed
        auto frameBuffer = m_vpRenderDelegate->GetFrameBuffer();
        FrameBufferSpec *spec = frameBuffer->GetSpecifications();
        if ((uint32_t) m_viewportWidth != spec->width ||
            (uint32_t) m_viewportHeight != spec->height) {

            m_camera->SetViewportSize(m_viewportWidth, m_viewportHeight);
            frameBuffer->Resize((uint32_t) m_viewportWidth,
                                (uint32_t) m_viewportHeight);
        }

        m_vpRenderDelegate->GetRenderScene()->Sync();
        m_vpRenderDelegate->Render(m_camera.get());
    }

    void MainLayer::OnEvent(Event &event) {
        m_camera->OnEvent(event);
    }

    bool MainLayer::OnWindowResizeEvent(WindowResizeEvent &event) {
        return false;
    }

    void MainLayer::OnImGuiRender() {
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImGui::GetStyleColorVec4(ImGuiCol_TitleBg));

        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        window_flags |= ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoCollapse |
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove |
                        ImGuiWindowFlags_NoBringToFrontOnFocus |
                        ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("MainDockSpace", nullptr, window_flags);

        // Pop the rounding, border & padding style vars set previously
        ImGui::PopStyleVar(3);

        // Submit the DockSpace
        ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMainMenuBar()) {

            if(ImGui::BeginMenu("File")) {

                if (ImGui::MenuItem("New")) { NewScene(); }
                if (ImGui::MenuItem("Open")) { OpenScene("test_scene.rbnd"); }
                if (ImGui::MenuItem("Save")) { RBND_INFO("Saving the current scene !"); }

                ImGui::EndMenu(); // File
            }

            if (ImGui::BeginMenu("View")) {

                if (ImGui::BeginMenu("Tool Windows")) {

                    bool m_showSceneHierarchy = m_sceneHierarchyWid.IsVisible();
                    if (ImGui::MenuItem("Scene Hierarchy", nullptr, &m_showSceneHierarchy))
                        m_sceneHierarchyWid.SetVisible(m_showSceneHierarchy);

                    bool m_showAttributeView = m_attributeViewWid.IsVisible();
                    if (ImGui::MenuItem("Attribute View", nullptr, &m_showAttributeView))
                        m_attributeViewWid.SetVisible(m_showAttributeView);

                    ImGui::EndMenu(); // UI Elements
                }

                ImGui::EndMenu(); // View
            }

            ImGui::EndMainMenuBar(); // Main menu bar
        }

        ImGui::End(); // MainDockSpace

        ImGui::PopStyleColor();

        // Render Scene Hierarchy widget
        m_sceneHierarchyWid.OnImGuiRender();

        // Set last selected Entity to the Attribute View
        auto &selection = m_sceneHierarchyWid.Selection();
        if (selection.empty())
            m_attributeViewWid.SetEntity(nullptr);
        else
            m_attributeViewWid.SetEntity(&selection[selection.size() - 1]);

        // Render Attribute View widget
        m_attributeViewWid.OnImGuiRender();

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

            Hop::RenderHints renderHints = m_vpRenderDelegate->GetRenderHints();
            if (ImGui::BeginMenu("Display mode")) {

                if (ImGui::MenuItem("Wireframe", nullptr,
                                    renderHints.displayMode == Hop::DisplayMode::Wireframe)) {
                    renderHints.displayMode = Hop::DisplayMode::Wireframe;
                    m_vpRenderDelegate->SetRenderHints(renderHints);
                }
                if (ImGui::MenuItem("Shaded", nullptr,
                                    renderHints.displayMode == Hop::DisplayMode::SmoothShaded)) {
                    renderHints.displayMode = Hop::DisplayMode::SmoothShaded;
                    m_vpRenderDelegate->SetRenderHints(renderHints);
                }

                ImGui::EndMenu(); // Display Mode
            }

            ImGui::PopStyleVar();
            ImGui::EndMenuBar();
        }

        uint64_t textureID = std::dynamic_pointer_cast<Hop::FrameBuffer>(m_vpRenderDelegate->GetFrameBuffer())->GetColorAttachmentID();
        ImGui::Image(reinterpret_cast<void *>(textureID),
                     ImVec2(m_viewportWidth, m_viewportHeight),
                     ImVec2{0, 1}, ImVec2{1, 0});

        ImGui::End();
        ImGui::PopStyleVar();

        // Render Attribute View widget
        m_renderView.OnImGuiRender();

        ImGui::ShowDemoWindow();
    }

    void MainLayer::NewScene() {
        RBND_INFO("New scene ...");

        auto scene = Scene::New();
        m_scene.reset(scene);

        // Remove the scene from the render delegates / render scenes
        m_vpRenderDelegate->GetRenderScene()->UnbindScene();
        m_renderView.GetRenderDelegate()->GetRenderScene()->UnbindScene();

        // Reset the scene hierarchy widget
        m_sceneHierarchyWid.SetScene(m_scene);
    }

    void MainLayer::OpenScene(const std::string& name) {
        RBND_INFO("Opening scene ...");

        if (auto scene = Scene::Open(name)) {
            RBND_INFO("Scene %s opened successfully !", name.c_str());
            m_scene.reset(scene);

            // Update render scenes from new scene data
            m_vpRenderDelegate->GetRenderScene()->BindScene(m_scene.get());
            m_renderView.GetRenderDelegate()->GetRenderScene()->BindScene(m_scene.get());

            // Reset the scene hierarchy widget
            m_sceneHierarchyWid.SetScene(m_scene);
        }
    }

}
