//
// Created by tvallentin on 07/03/2022.
//

#include "embree3/rtcore.h"

#include "Raytracer.h"

#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "BSDF.h"
#include "Sampling.h"


namespace Bounce {


    void Raytracer::Render(float *pixels,
                           const unsigned int &width,
                           const unsigned int &height,
                           const Camera *camera) const {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < height; y++)
                RenderPixel(x, y, pixels, width, height, camera);
    }


    void Raytracer::RenderPixel(unsigned int x,
                                unsigned int y,
                                float *pixels,
                                unsigned int width,
                                unsigned int height,
                                const Camera *camera) const {
        int nSample = 60;
        Color3f L(0);
        for (int s = 0; s < nSample; s++) {
            // Generate camera ray
            Ray ray;
            Vec2f sample = (Vec2f(x, y) + RandomVector2(-0.5, 0.5)) / Vec2f(width, height);
            float apertureMultiplier = camera->Sample(sample, ray);

            L += ComputeIllumination(ray) * apertureMultiplier;
        }
        L /= (float) nSample;

        const unsigned int index = (x + y * width) * 3;
        pixels[index] = L.x;
        pixels[index + 1] = L.y;
        pixels[index + 2] = L.z;
    }

    Color3f Raytracer::ComputeIllumination(Ray &ray, int depth) const {
        if (depth++ > 2)
            return Color3f(0);

        RTCIntersectContext context;
        rtcInitIntersectContext(&context);

        // Intersect ray with the scene
        rtcIntersect1(scene->rtcScene, &context, AsRTCRayHit(ray));

        // If the ray hit, set the color to red and send a shadow ray
        if (ray.geomID != RTC_INVALID_GEOMETRY_ID) {
            Vec3f wo = -ray.direction;
            Vec3f wi;

            // Generating BSDF and giving it to the material to fill it with BxDFs
            BSDF bsdf(ray);
            scene->defaultMaterial->FillBSDF(ray, bsdf);

            // Evaluating the BSDF
            float pdf;
            Color3f f = bsdf.Sample(wo, wi, pdf);

            // Returning black if pdf is null (to avoid divide by zero error)
            if (pdf == 0)
                return Color3f(0.0f);

            // Returning black if the transmitted light is too low
            if (f.x + f.y + f.z < 10e-4)
                return Color3f(0.0f);

            // Reverting the normal if it is not in the same direction as the incoming ray
            Vec3f N = ray.Ng.normalized();
            if (wo.dot(N) < 0) {
                N = -N;
            }

            // Moving the hit point a tiny bit along the normal to avoid hitting the same surface again
            ray = Ray(ComputeHitPoint(ray) + N * 10e-4, wi);

            return f * ComputeIllumination(ray, depth) * std::abs(wi.dot(N)) / pdf;
        }

        return Color3f(ray.direction.y * 0.5f + 0.5f);
    }

}
