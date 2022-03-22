//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_APPLICATIONEVENT_H
#define BOUNCE_GUI_APPLICATIONEVENT_H

#include "App/Core/Event.h"

namespace Bounce::Gui {

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(const uint32_t &width, const uint32_t &height)
                : m_width(width), m_height(height) {}

        [[nodiscard]] uint32_t GetWidth() const { return m_width; }
        [[nodiscard]] uint32_t GetHeight() const { return m_height; }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory_Application)
    private:
        uint32_t m_width, m_height;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory_Application)
    };

}

#endif //BOUNCE_GUI_APPLICATIONEVENT_H
