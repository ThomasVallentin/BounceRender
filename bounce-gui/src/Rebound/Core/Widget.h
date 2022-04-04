//
// Created by Thomas Vallentin on 01/04/2022.
//

#ifndef RBND_WIDGET_H
#define RBND_WIDGET_H

#include <string>

namespace Rebound {

    class Widget {
    public:
        Widget(const std::string &title) : m_title(title) {}

        inline bool IsVisible() const { return m_visibility; }
        inline void SetVisible(const bool &value) { m_visibility = value; }
        inline void Show() { m_visibility = true; }
        inline void Hide() { m_visibility = false; }

        void OnImGuiRender();
        virtual void PreRender() {};
        virtual void Render() = 0;
        virtual void PostRender() {};

    private:
        bool m_visibility = true;
        std::string m_title;
    };

}

#endif //RBND_WIDGET_H
