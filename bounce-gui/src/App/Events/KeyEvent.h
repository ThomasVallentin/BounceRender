//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_KEYEVENT_H
#define BOUNCE_GUI_KEYEVENT_H

#include "App/Core/Event.h"
#include "App/Core/KeyCodes.h"

namespace Bounce::Gui {
    class KeyEvent : public Event {
    public:
        explicit KeyEvent(const KeyCode &key)
                : m_key(key) {}

        [[nodiscard]] KeyCode GetKey() const { return m_key; }

        EVENT_CLASS_CATEGORY(EventCategory_Keyboard | EventCategory_Input)

    private:
        KeyCode m_key;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        explicit KeyPressedEvent(const KeyCode &key, const bool &repeat)
                : KeyEvent(key), repeat(repeat) {}

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool repeat;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        explicit KeyReleasedEvent(const KeyCode &key)
                : KeyEvent(key) {}

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        explicit KeyTypedEvent(const KeyCode &key)
                : KeyEvent(key) {}

        EVENT_CLASS_TYPE(KeyTyped)
    };

}

#endif //BOUNCE_GUI_KEYEVENT_H
