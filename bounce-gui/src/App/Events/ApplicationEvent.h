//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_APPLICATIONEVENT_H
#define BOUNCE_APPLICATIONEVENT_H

#include "App/Event.h"

namespace Bounce::Gui {

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(const unsigned int &width, const unsigned int &height)
                : m_width(width), m_height(height) {}

        [[nodiscard]] unsigned int GetWidth() const { return m_width; }
        [[nodiscard]] unsigned int GetHeight() const { return m_height; }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    private:
        unsigned int m_width, m_height;
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

}

#endif //BOUNCE_APPLICATIONEVENT_H
