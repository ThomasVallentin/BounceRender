//
// Created by tvallentin on 08/03/2022.
//

#include "global.h"


void ErrorFunction(void* userPtr, enum RTCError error, const char* str)
{
    printf("# Error %d: %s\n", error, str);
}


namespace Bounce {
    RTCDevice globalDevice = nullptr;
}

bool InitializeBounce() {
    Bounce::globalDevice = rtcNewDevice(nullptr);

    if (!Bounce::globalDevice) {
        printf("Error %d: Could not create device\n", rtcGetDeviceError(nullptr));
        return false;
    }

    rtcSetDeviceErrorFunction(Bounce::globalDevice, ErrorFunction, nullptr);
    return true;
}


void ReleaseBounce() {
    rtcReleaseDevice(Bounce::globalDevice);
}