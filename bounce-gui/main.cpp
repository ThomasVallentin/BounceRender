#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
    // GL 3.0 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
//    glfwSwapInterval(1); // Enable vsync

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/* -------------------------------------------------------------------------- */


//bool writePixels(const std::string &filename,
//                 float *pixels,
//                 int width,
//                 int height) {
//    std::unique_ptr<OIIO::ImageOutput> out = OIIO::ImageOutput::create(filename);
//    if (!out) {
//        printf("Could not create the ImageOutput : %s\n", out->geterror().c_str());
//        return false;
//    }
//
//    OIIO::ImageSpec spec(width, height, 3, OIIO::TypeDesc::FLOAT);
//    if (!out->open(filename, spec)) {
//        printf("Could not open  : %s\n", out->geterror().c_str());
//        return false;
//    }
//
//    if (!out->write_image(OIIO::TypeDesc::FLOAT, pixels)) {
//        printf("Could not write the image : %s\n", out->geterror().c_str());
//        return false;
//    }
//
//    out->close();
//    printf("Successfully wrote image to %s\n", filename.c_str());
//
//    return true;
//}
//
//
//int main(int argc, char *argv[])
//{
//    const unsigned int width = 640, height = 480;
//    const int channels = 3;  // RGB
//    float pixels[width * height * channels];
//
//    // Initialize the api
//    InitializeBounce();
//
//    // Create new scene
//    std::string filename(argc > 0 ?
//                         "/code/Bounce/resources/geometries/wheelBarrow/wheelBarrow_LOD0.abc"
//                         : argv[1]);
//    Scene scene = Scene::Open(filename);  // Temp function before using a proper Scene management
//    scene.Commit();  // Apply the changes to the embree scene
//
//    Camera camera;
//    camera.transform.rotate(Imath_2_5::Vec3<float>(0.2f, 0.0f, 0.0f));
//    camera.transform.translate(Imath_2_5::Vec3<float>(0.0f, 50.0f, -300.0f));
//    camera.f = 1000.0f;
//
//    Raytracer tracer(&scene);
//    tracer.Render(pixels, width, height, camera);
//
//    writePixels("/code/Bounce/renders/output.png", pixels, width, height);
//
//    // Cleanup before quitting
//    scene.Release();
//    ReleaseBounce();
//
//    return 0;
//}
