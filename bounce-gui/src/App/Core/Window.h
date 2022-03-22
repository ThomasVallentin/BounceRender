//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_WINDOW_H
#define BOUNCE_GUI_WINDOW_H

#include "Event.h"

#include <functional>
#include <string>

namespace Bounce::Gui {

    struct WindowProperties {
        int height = 480;
        int width = 640;
        std::string title = "Bounce::Gui::Window";
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        [[nodiscard]] virtual uint32_t GetWidth() const = 0;
        [[nodiscard]] virtual uint32_t GetHeight() const = 0;
        virtual void SetEventCallback(EventCallbackFn callback) = 0;

        virtual void* GetNativeWindow() const = 0;

        static Window *Create(const WindowProperties &properties = WindowProperties());
    };
}

#endif //BOUNCE_GUI_WINDOW_H
