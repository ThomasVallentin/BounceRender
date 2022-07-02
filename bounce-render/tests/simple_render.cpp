//
// Created by Thomas Vallentin on 16/03/2022.
//

#include "BounceRender/Core/Scene.h"
#include "BounceRender/Core/Raytracer.h"
#include "BounceRender/Core/Camera.h"

#include <OpenImageIO/imageio.h>


using namespace Bounce;

int main() {
    InitializeBounce();

    Scene scene = Scene::Open(R"(C:\dev\BounceRender\bounce-render\resources\geometries\wheelBarrow\wheelBarrow_LOD3.abc)");
    scene.Commit();

    const int width    = 640;
    const int height   = 360;
    const int channels = 3;
    float *pixels = new float[width * height * channels];
    Raytracer tracer(&scene);

    Mat4f camTransform;
//    camTransform.rotate(Vec3f(0, M_PI_2, 0));
    camTransform.rotate(Vec3f(-0.4, M_PI_2 - 1, 0));
    camTransform.translate(Vec3f(0, 18, 380));
    ThinLensCamera camera(camTransform, {width, height}, {21.946, 16.002}, 50.0, 330.0, 1.5);

    tracer.Render(pixels, width, height, &camera);

    ReleaseBounce();

    std::string filename = R"(C:\dev\BounceRender\bounce-render\renders\simple_render.png)";
    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create (filename);
    if (! out)
        return 1;

    OIIO::ImageSpec spec (width, height, channels, OIIO::TypeDesc::UINT8);
    out->open (filename, spec);
    out->write_image (OIIO::TypeDesc::FLOAT, pixels);
    out->close ();

    return 0;
}
