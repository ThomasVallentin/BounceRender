//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_APPLICATION_H
#define BOUNCE_GUI_APPLICATION_H

#include "Window.h"
#include "Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Layers/ImGuiLayer.h"

#include <core/Raytracer.h>
#include <core/Scene.h>

#include <boost/filesystem.hpp>
#include <OpenImageIO/imageio.h>

#include <iostream>


namespace Bounce::Gui {
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


#endif //BOUNCE_GUI_APPLICATION_H
