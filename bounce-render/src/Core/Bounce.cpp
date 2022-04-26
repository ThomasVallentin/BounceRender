//
// Created by Thomas Vallentin on 16/03/2022.
//

#include "Bounce.h"

namespace Bounce {

    void HandleEmbreeError(void* userPtr, enum RTCError error, const char* str)
    {
        printf("# Bounce Embree ERROR %d: %s\n", error, str);
    }
    RTCDevice g_globalDevice;

    bool InitializeBounce() {
        // Returning if Bounce is already initialized
        if (Bounce::g_globalDevice)
            return true;

        // Create the global RTCDevice used throughout the API
        Bounce::g_globalDevice = rtcNewDevice(nullptr);

        if (!Bounce::g_globalDevice) {
            printf("Error %d: Could not create device\n",
                   rtcGetDeviceError(nullptr));
            return false;
        }

        // Initialize embree error logging function
        rtcSetDeviceErrorFunction(Bounce::g_globalDevice,
                                  HandleEmbreeError,
                                  nullptr);
        return true;
    }

    void ReleaseBounce() {
        rtcReleaseDevice(Bounce::g_globalDevice);
    }

    RTCDevice GetGlobalDevice() {
        return Bounce::g_globalDevice;
    }

}
