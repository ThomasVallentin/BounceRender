//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_EVENT_H
#define BOUNCE_GUI_EVENT_H

#include <iostream>
#include <functional>

#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return  category; }
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                               EventType GetType() const override { return GetStaticType(); } \
                               const char* GetName() const override { return #type; }

namespace Bounce::Gui {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize,
        KeyPressed, KeyReleased, KeyTyped,
        MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategory_Application     = 1 << 0,
        EventCategory_Input           = 1 << 1,
        EventCategory_Keyboard        = 1 << 2,
        EventCategory_Mouse           = 1 << 3,
        EventCategory_MouseButton     = 1 << 4,
    };

    class Event {
    public:

        bool handled = false;

        virtual EventType GetType() const = 0;
        [[nodiscard]] virtual int GetCategoryFlags() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.GetName();
    }

    // TODO(tvallentin): Events are handled directly instead of being processed through a queue/stack.
    //                   This needs to be improved later.
    // Class mande to dispatch events in Layer::OnEvent reimplementations. Use it like so :
    // void Layer::OnEvent(Event &event) {
    //     EventDispatcher dispatcher(event);
    //     dispatcher.Dispatch<SomeEventClass>(BIND_EVENT_FUNC(RenderLayer::OnASpecificEventClass));
    // }
    //
    // bool RenderLayer::OnASpecificEventClass(SomeEventClass &event) {
    //     <insert your code here>
    //     return true/false (whether the callback handled the event or if it will be propagated
    //                        across the next layers of the layerstack);
    // }
    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        explicit EventDispatcher(Event& event)
                : m_event(event) {}

        // Dispatch is in charge of casting the event to the proper type if it matches it
        // and calling the given function with the casted result.
        // The result is whether the event matches the wanted callback or not.
        template<typename T>
        bool Dispatch(EventFn<T> func) {
            // If event type matches dispatched type
            if (m_event.GetType() == T::GetStaticType()) {
                // Cast m_event as a T instance and call func with it.
                m_event.handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }
        
    private:
        Event &m_event;
    };

// Use this macro to bind a function to a "slot" inside classes that handle events
// like Application, Window, Layer, etc...
#define BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

}


#endif //BOUNCE_GUI_EVENT_H
