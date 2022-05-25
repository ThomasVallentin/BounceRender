//
// Created by Thomas Vallentin on 19/03/2022.
//

#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


namespace Hop {

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_windowHandle);

        // Initialize GLAD
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        printf("# Successfully loaded OpenGL !\n");
        printf("OpenGL info :\n");
        printf("  Vendor: %s\n", glGetString(GL_VENDOR));
        printf("  Renderer: %s\n", glGetString(GL_RENDERER));
        printf("  Version: %s\n", glGetString(GL_VERSION));

        // Enabling depth
        glEnable(GL_DEPTH_TEST);
    }


    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_windowHandle);
    }

}