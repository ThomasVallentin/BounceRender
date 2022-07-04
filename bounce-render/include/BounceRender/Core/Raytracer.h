//
// Created by tvallentin on 07/03/2022.
//

#ifndef BOUNCE_RAYTRACER_H
#define BOUNCE_RAYTRACER_H

#include "Bounce.h"

#include <cstdio>


namespace Bounce {

    enum class IntegratorState {
        NONE = 0,
        RUNNING,
        STOPPED,
        PAUSE
    };

    class Raytracer {
    public:
        Raytracer() : scene(nullptr) {};

        explicit Raytracer(Scene *scene) : scene(scene) {}

        void Render(float *pixels,
                    const unsigned int &width,
                    const unsigned int &height,
                    const unsigned int &samples,
                    const Camera *camera);

        void Stop();

    protected:
        void RenderPixel(const uint32_t &x,
                         const uint32_t &y,
                         const uint32_t &sampleNum,
                         float *pixels,
                         unsigned int width,
                         unsigned int height,
                         const Camera *camera) const;

        Color3f ComputeIllumination(Ray &ray, int depth=0) const;

        Scene *scene;

        IntegratorState m_status = IntegratorState::STOPPED;
        IntegratorState m_nextStatus = IntegratorState::NONE;
    };

}

#endif //BOUNCE_RAYTRACER_H
