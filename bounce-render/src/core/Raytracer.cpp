//
// Created by tvallentin on 07/03/2022.
//

#include "embree3/rtcore.h"

#include "Raytracer.h"
#include "Scene.h"
#include "BSDF.h"
#include "Sampling.h"




RTCRayHit makeRayHit(const Camera &camera,
                     float x, float y,
                     const unsigned int width,
                     const unsigned int height) {
    Vec3f dir(-0.5f * float(width) + x,
                   0.5f * float(height) - y,
                   camera.f);
    dir.normalize();
    // Todo: There is probably a better way to do that
    dir = Imath::extractQuat(camera.transform).rotateVector(dir);
    dir.normalize();

    return CreateRayHit(camera.transform.translation(), dir);
}




void Raytracer::Render(float *pixels,
                       const unsigned int &width,
                       const unsigned int &height,
                       const Camera &camera) const {
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            RenderPixel(x, y, pixels, width, height, camera);
}


void Raytracer::RenderPixel(unsigned int x,
                            unsigned int y,
                            float *pixels,
                            unsigned int width,
                            unsigned int height,
                            const Camera &camera)  const {
    int nSample = 20;
    Color3f L(0);
    for (int s=0; s < nSample; s++) {
        // Generate camera ray
        RTCRayHit rayhit = makeRayHit(camera, x+RandomReal(-.5, .5), y+RandomReal(-.5, .5), width, height);

        L += ComputeIllumination(rayhit, 0);
    }
    L /= (float)nSample;

    const unsigned int index = (x + y * width) * 3;
    pixels[index] = L.x;
    pixels[index + 1] = L.y;
    pixels[index + 2] = L.z;
}

Color3f Raytracer::ComputeIllumination(RTCRayHit rayhit, int depth) const {
    if (depth++ > 4)
        return Color3f(0);

    RTCIntersectContext context;
    rtcInitIntersectContext(&context);

    // Intersect ray with the scene
    rtcIntersect1(scene->rtcScene, &context, &rayhit);

    // If the ray hit, set the color to red and send a shadow ray
    if (rayhit.hit.geomID != RTC_INVALID_GEOMETRY_ID) {
        Vec3f wo = -RayDir(rayhit), wi;

        // Generating BSDF and giving it to the material to fill it with BxDFs
        BSDF bsdf(rayhit);
        scene->defaultMaterial->FillBSDF(rayhit, bsdf);

        // Evaluating the BSDF
        float pdf;
        Color3f f = bsdf.Sample(wo, wi, pdf);

        // Returning black if pdf is null (avoid divide by zero error)
        if (pdf == 0)
            return Color3f(0.0f);

        // Returning black if the transmitted light is too low
        if (f.length2() < 10e-6)
            return Color3f(0.0f);

        Vec3f N =  Vec3f(rayhit.hit.Ng_x, rayhit.hit.Ng_y, rayhit.hit.Ng_z).normalized();
        if (wo.dot(N) < 0) {
            N = -N;
        }
        rayhit = CreateRayHit(HitPoint(rayhit) + N * 10e-4, wi);
        return f * ComputeIllumination(rayhit, depth) * std::abs(wi.dot(N)) / pdf;
    }

    return Color3f(rayhit.ray.dir_y * 0.5f + 0.5f);
}
