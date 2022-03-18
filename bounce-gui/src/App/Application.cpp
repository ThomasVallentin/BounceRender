//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "Application.h"

#include <glad/glad.h>

namespace Bounce::Gui {

    Application* Application::s_instance = nullptr;

    Application::Application() {
        if (s_instance) {
            std::cerr << "Application already exists" << std::endl;
            return;
        }
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));

        m_imGuiLayer = new ImGuiLayer();
        AddLayer(m_imGuiLayer);
    }

    int Application::Run() {
        m_isRunning = true;

        while(m_isRunning) {
            // Clear background
            glClearColor(0.2, 0.2, 0.2, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto layer : m_layerStack) {
                layer->OnUpdate();
            }

            m_imGuiLayer->Begin();
            for (auto layer : m_layerStack) {
                layer->OnImGuiRender();
            }
            m_imGuiLayer->End();


            m_window->OnUpdate();
        }

        return 0;
    }

    void Application::AddLayer(Layer *layer) {
        m_layerStack.AddLayer(layer);
    }

    void Application::RemoveLayer(Layer *layer) {
        m_layerStack.RemoveLayer(layer);
    }

    void Application::OnEvent(Event &event) {
        // Calling all the layers of the layer stack backwards (higher in first),
        // breaking as soon as a layer handle the event
        for (auto it = m_layerStack.end() ; it != m_layerStack.begin() ; ) {
            (*--it)->OnEvent(event);
            if (event.handled)
                break;
        }

        if (event.GetType() == EventType::WindowClose)
            OnWindowClose(*dynamic_cast<WindowCloseEvent*>(&event));
    }

    void Application::OnWindowClose(WindowCloseEvent &event) {
        m_isRunning = false;
        event.handled = true;
    }

}



////        // Setup Dear ImGui context
////        IMGUI_CHECKVERSION();
////        ImGui::CreateContext();
////        ImGuiIO& io = ImGui::GetIO(); (void)io;
////        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
////        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
////        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
////        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
////        //io.ConfigViewportsNoAutoMerge = true;
////        //io.ConfigViewportsNoTaskBarIcon = true;
////
////        // Setup Dear ImGui style
////        ImGui::StyleColorsDark();
////
////        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
////        ImGuiStyle& style = ImGui::GetStyle();
////        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
////        {
////            style.WindowRounding = 3.0f;
////            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
////        }
////
////        // Setup Platform/Renderer backends
////        ImGui_ImplGlfw_InitForOpenGL(window, true);
////        ImGui_ImplOpenGL3_Init(glsl_version);
//
////        Scene scene;
////        scene.LoadTestGeometry();
////        scene.Commit();
////
////        Camera camera;
////        camera.transform.rotate(Vec3f(0.2f, 0.0f, 0.0f));
////        camera.transform.translate(Vec3f(0.0f, 0.0f, -10.0f));
////        camera.f = 1000.0f;
//std::cout << m_window << std::endl;
//
//const int width = 500, height = 500;
//float *pixels = new float[width*height*3];
////        Raytracer raytracer(&scene);
////        raytracer.Render(pixels, width, height, camera);
//
//unsigned int texture;
//glGenTextures(1, &texture);
//glBindTexture(GL_TEXTURE_2D, texture);
//// set the texture wrapping parameters
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//// set texture filtering parameters
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//// load image, create texture and generate mipmaps
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16, width, height, 0, GL_RGB, GL_FLOAT, pixels);
//glGenerateMipmap(GL_TEXTURE_2D);
//
//// Main loop
//while (m_isRunning) {
////            // Start the Dear ImGui frame
////            ImGui_ImplOpenGL3_NewFrame();
////            ImGui_ImplGlfw_NewFrame();
////            ImGui::NewFrame();
////
//// Clear background
//glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
//glClear(GL_COLOR_BUFFER_BIT);
//
//m_window->OnUpdate();
//
////            ImGui::Begin("Image");
////            ImGui::Image((void*)(intptr_t)texture, ImVec2(width, height));
////            ImGui::End();
////
////            // Rendering
////            ImGui::Render();
////            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
////
////            // Update and Render additional Platform Windows
////            // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
////            //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
////            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
////            {
////                GLFWwindow* backup_current_context = glfwGetCurrentContext();
////                ImGui::UpdatePlatformWindows();
////                ImGui::RenderPlatformWindowsDefault();
////                glfwMakeContextCurrent(backup_current_context);
////            }
//}
//////    // Cleanup
////        ImGui_ImplOpenGL3_Shutdown();
////        ImGui_ImplGlfw_Shutdown();
////        ImGui::DestroyContext();
//
////    App::Release();
