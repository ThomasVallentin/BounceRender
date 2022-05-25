//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef RBND_APPLICATION_H
#define RBND_APPLICATION_H

#include "Window.h"
#include "Event.h"
#include "LayerStack.h"
#include "Rebound/Events/ApplicationEvent.h"
#include "Rebound/Layers/ImGuiLayer.h"

#include <iostream>


namespace Rebound {
    class Application {
    public:
        Application();
        ~Application() = default;

        int Run();
        void OnEvent(Event &event);
        inline Window& GetWindow() { return *m_window; }

        void AddLayer(Layer* layer);
        void RemoveLayer(Layer* layer);

    public:
        inline static Application& Get() { return *s_instance;}

    private:
        void OnWindowClose(WindowCloseEvent &event);

        std::unique_ptr<Window> m_window;
        ImGuiLayer* m_imGuiLayer;
        LayerStack m_layerStack;
        bool m_isRunning = true;

    private:
        static Application* s_instance;
    };
}


#endif //RBND_APPLICATION_H
