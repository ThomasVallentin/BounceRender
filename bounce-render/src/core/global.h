//
// Created by tvallentin on 08/03/2022.
//

#ifndef BOUNCE_GLOBAL_H
#define BOUNCE_GLOBAL_H

#include "embree3/rtcore.h"

#include <cstdio>
#include <functional>


namespace Bounce {
    extern RTCDevice globalDevice;
}

extern bool InitializeBounce();
extern void ReleaseBounce();



#endif //BOUNCE_GLOBAL_H
