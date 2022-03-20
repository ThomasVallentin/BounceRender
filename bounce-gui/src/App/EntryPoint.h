//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef BOUNCE_GUI_ENTRYPOINT_H
#define BOUNCE_GUI_ENTRYPOINT_H

#include "Application.h"

namespace Bounce::Gui {
    // To redefined
    extern Application* CreateApplication();
}

// This will be the application entry point
int main(int argc, char *argv[]) {
    Bounce::Gui::Application* app = Bounce::Gui::CreateApplication();
    int returnCode = app->Run();
    delete app;

    return returnCode;
}

#endif //BOUNCE_GUI_ENTRYPOINT_H
