//
// Created by tvallentin on 07/03/2022.
//


#include "Raytracer.h"

#include "Ray.h"
#include "Camera.h"
#include "Scene.h"
#include "BSDF.h"
#include "Sampling.h"
#include "Logging.h"

#include <embree3/rtcore.h>

#include <tbb/parallel_for.h>

namespace Bounce {

    void Raytracer::Stop() {
        if(m_status == IntegratorState::RUNNING)
            m_nextStatus = IntegratorState::STOPPED;
    }

    void Raytracer::Render(float *pixels,
                           const unsigned int &width,
                           const unsigned int &height,
                           const unsigned int &samples,
                           const Camera *camera) {

        m_status = IntegratorState::RUNNING;

        tbb::parallel_for(tbb::blocked_range<uint32_t>(0, samples),
                          [&](const tbb::blocked_range<uint32_t> &range){

            for (uint32_t sample=range.begin() ; sample < range.end() ; sample++)
                for (int y = 0; y < height; y++)
                    for (int x = 0; x < width; x++) {

                        if (m_nextStatus == IntegratorState::STOPPED) {
                            return;
                        }

                        RenderPixel(x, y,
                                    sample,
                                    pixels,
                                    width, height,
                                    camera);
                    }
        });

        m_status = IntegratorState::STOPPED;
        m_nextStatus = IntegratorState::NONE;
    }

    void Raytracer::RenderPixel(const uint32_t &x,
                                const uint32_t &y,
                                const uint32_t &sampleNum,
                                float *pixels,
                                unsigned int width,
                                unsigned int height,
                                const Camera *camera) const {
        const unsigned int index = (x + y * width) * 3;
        Color3f L(0);

        // Generate camera ray
        Ray ray;
        Vec2f sample = (Vec2f(x, y) + RandomVector2(-0.5, 0.5)) / Vec2f(width, height);
        float apertureMultiplier = camera->Sample(sample, ray);

        L += ComputeIllumination(ray) * apertureMultiplier;

        // Accumulate L inside the pixels
        L = (Vec3f(pixels[index],
                   pixels[index + 1],
                   pixels[index + 2]) * (float) sampleNum + L) / (sampleNum + 1.0f);

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

        // If the ray doesn't hit anything, "sample"a pseudo environment light
        if (ray.geomID == RTC_INVALID_GEOMETRY_ID) {
            return Color3f(ray.direction.y * 0.5f + 0.5f);
        }

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

}
