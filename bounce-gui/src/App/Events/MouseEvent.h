//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_MOUSEEVENT_H
#define BOUNCE_GUI_MOUSEEVENT_H

#include "App/Core/Event.h"

namespace Bounce::Gui {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float &x, const float &y)
                : m_x(x), m_y(y) {}

        [[nodiscard]]inline float GetX() const { return m_x; }
        [[nodiscard]]inline float GetY() const { return m_y; }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_x, m_y;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(const float &x, const float &y)
                : m_x(x), m_y(y) {}

        [[nodiscard]]inline float GetOffsetX() const { return m_x; }
        [[nodiscard]]inline float GetOffsetY() const { return m_y; }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_x, m_y;
    };


    class MouseButtonEvent : public Event {
    public:
        explicit MouseButtonEvent(const int &button)
                : m_button(button) {}

        [[nodiscard]] int GetButton() const { return m_button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        int m_button;
    };

    class MousePressedEvent : public MouseButtonEvent {
    public:
        explicit MousePressedEvent(const int &button)
                : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseReleasedEvent : public MouseButtonEvent {
    public:
        explicit MouseReleasedEvent(const int &button)
                : MouseButtonEvent(button) {}

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };



}

#endif //BOUNCE_GUI_MOUSEEVENT_H
