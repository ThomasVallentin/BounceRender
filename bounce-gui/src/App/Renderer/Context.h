//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef BOUNCE_GUI_CONTEXT_H
#define BOUNCE_GUI_CONTEXT_H


namespace Bounce::Gui {

    class RenderContext {
    public:
        RenderContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}


#endif //BOUNCE_GUI_CONTEXT_H
