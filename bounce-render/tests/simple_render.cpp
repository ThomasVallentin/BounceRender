//
// Created by Thomas Vallentin on 16/03/2022.
//

#include "BounceRender/Core/Scene.h"
#include "BounceRender/Core/Raytracer.h"

#include <OpenImageIO/imageio.h>


using namespace Bounce;

int main() {
    InitializeBounce();

    Scene scene = Scene::Open(R"(C:\dev\BounceRender\bounce-render\resources\geometries\wheelBarrow\wheelBarrow_LOD0.abc)");
    scene.Commit();

    Mat4f camTransform;
    camTransform.rotate(Vec3f(0.4, 2.5, 0));
    camTransform.translate(Vec3f(0, 0, -200));
    Camera camera{camTransform, 800};

    const int width = 1000, height = 1000, channels = 3;
    float *pixels = new float[width * height * channels];
    Raytracer tracer(&scene);
    tracer.Render(pixels, width, height, camera);

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
