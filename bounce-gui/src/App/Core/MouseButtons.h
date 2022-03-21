//
// Created by Thomas Vallentin on 21/03/2022.
//

#ifndef BOUNCE_MOUSEBUTTONS_H
#define BOUNCE_MOUSEBUTTONS_H

namespace Bounce::Gui {

    enum class MouseButton {
        Button0         = 0,
        Button1         = 1,
        Button2         = 2,
        Button3         = 3,
        Button4         = 4,
        Button5         = 5,
        Button6         = 6,
        Button7         = 7,

        ButtonLast      = Button7,
        ButtonLeft      = Button0,
        ButtonRight     = Button1,
        ButtonMiddle    = Button2
    };

}

#endif //BOUNCE_MOUSEBUTTONS_H
