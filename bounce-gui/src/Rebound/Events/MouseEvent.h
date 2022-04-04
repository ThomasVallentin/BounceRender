//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef RBND_MOUSEEVENT_H
#define RBND_MOUSEEVENT_H

#include "Rebound/Core/Event.h"

namespace Rebound {

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float &x, const float &y)
                : m_x(x), m_y(y) {}

        [[nodiscard]]inline float GetX() const { return m_x; }
        [[nodiscard]]inline float GetY() const { return m_y; }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input)

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
        EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input)

    private:
        float m_x, m_y;
    };


    class MouseButtonEvent : public Event {
    public:
        explicit MouseButtonEvent(const int &button)
                : m_button(button) {}

        [[nodiscard]] int GetButton() const { return m_button; }

        EVENT_CLASS_CATEGORY(EventCategory_Mouse | EventCategory_Input)

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

#endif //RBND_MOUSEEVENT_H
