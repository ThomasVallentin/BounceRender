//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef RBND_CONTEXT_H
#define RBND_CONTEXT_H


namespace Rebound {

    class RenderContext {
    public:
        RenderContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}


#endif //RBND_CONTEXT_H
