//
// Created by tvallentin on 07/03/2022.
//

#ifndef BOUNCE_RAYTRACER_H
#define BOUNCE_RAYTRACER_H

#include <cstdio>

#include "Bounce.h"

namespace Bounce {

    class Scene;

    struct Camera {
        Mat4f transform;
        float f{};
    };

    class Raytracer {
    public:
        Raytracer() : scene(nullptr) {};

        explicit Raytracer(Scene *scene) : scene(scene) {}

        void Render(float *pixels,
                    const unsigned int &width,
                    const unsigned int &height,
                    const Camera &camera) const;

    protected:
        void RenderPixel(unsigned int x, unsigned int y,
                         float *pixels,
                         unsigned int width,
                         unsigned int height,
                         const Camera &camera) const;

        Color3f ComputeIllumination(RTCRayHit rayhit, int depth) const;

        Scene *scene;
    };

}

#endif //BOUNCE_RAYTRACER_H
