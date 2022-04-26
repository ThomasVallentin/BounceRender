//
// Created by Thomas Vallentin on 16/03/2022.
//

#include "Core/Scene.h"
#include "Core/Raytracer.h"

int main() {
    Bounce::InitializeBounce();

    Scene scene;
    scene.LoadTestGeometry();
    scene.Commit();

    Camera camera;
    const int width = 100, height = 100;
    float *pixels = new float[width*height*3];
    Raytracer tracer(&scene);
    tracer.Render(pixels, width, height, camera);

    Bounce::ReleaseBounce();

    return 0;
}
