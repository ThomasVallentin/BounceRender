//
// Created by Thomas Vallentin on 19/03/2022.
//

#ifndef HOP_CONTEXT_H
#define HOP_CONTEXT_H


namespace Hop {

    class RenderContext {
    public:
        RenderContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}


#endif //HOP_CONTEXT_H
