//
// Created by Thomas Vallentin on 17/03/2022.
//

#include "Application.h"

#include "Rebound/Backends/OpenGL/OpenGLShader.h"
#include "Rebound/Backends/OpenGL/OpenGLBuffer.h"
#include "Rebound/Backends/OpenGL/OpenGLContext.h"
#include "Rebound/Backends/OpenGL/OpenGLRenderer.h"

#include "Rebound/Scene/EntityRegistry.h"
#include "Rebound/Scene/Entity.h"
#include "Rebound/Scene/Entities/Xform.h"
#include "Rebound/Scene/Entities/Mesh.h"
#include "Rebound/Scene/Entities/Line.h"

#include <glad/glad.h>

namespace Rebound {

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

        // Initialize basic types
        EntityRegistry &registry = EntityRegistry::Get();
        registry.RegisterEntityType<Entity>();
        registry.RegisterEntityType<Xform>();
        registry.RegisterEntityType<Mesh>();
        registry.RegisterEntityType<Line>();
    }

    int Application::Run() {
        m_isRunning = true;

        while(m_isRunning) {
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
