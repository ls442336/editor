#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

#include "config.h"
#include "editor.h"

Editor editor;

void resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    editor.settings.updateWindowSize(width, height);
}

int main(int argc, char *argv[])
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(config::window::width,
                                          config::window::height,
                                          config::window::title,
                                          NULL,
                                          NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup callbacks
    glfwSetFramebufferSizeCallback(window, resize);

    glViewport(0, 0, config::window::width, config::window::height);

    // Init Editor
    editor.init();

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        editor.run();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
