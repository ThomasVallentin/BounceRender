//
// Created by Thomas Vallentin on 17/03/2022.
//

#ifndef RBND_ENTRYPOINT_H
#define RBND_ENTRYPOINT_H

#include "Application.h"

namespace Rebound {
    // To redefined
    extern Application* CreateApplication();
}

// This will be the application entry point
int main(int argc, char *argv[]) {
    Rebound::Application* app = Rebound::CreateApplication();
    int returnCode = app->Run();
    delete app;

    return returnCode;
}

#endif //RBND_ENTRYPOINT_H
