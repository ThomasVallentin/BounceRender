//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_KEYEVENT_H
#define BOUNCE_GUI_KEYEVENT_H

#include "App/Event.h"

namespace Bounce::Gui {
    class KeyEvent : public Event {
    public:
        explicit KeyEvent(const int &key)
                : m_key(key) {}

        [[nodiscard]] int GetKey() const { return m_key; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    private:
        int m_key;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        explicit KeyPressedEvent(const int &key, const bool &repeat)
                : KeyEvent(key), repeat(repeat) {}

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool repeat;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        explicit KeyReleasedEvent(const int &key)
                : KeyEvent(key) {}

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        explicit KeyTypedEvent(const int &key)
                : KeyEvent(key) {}

        EVENT_CLASS_TYPE(KeyTyped)
    };

}

#endif //BOUNCE_GUI_KEYEVENT_H
