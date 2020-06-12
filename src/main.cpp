#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>

#include "config.h"
#include "editor.h"

#include "freetype.h"
#include "resourcemanager.h"

Editor editor;

void resize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    editor.settings.updateWindowSize(width, height);
}

int main(int argc, char *argv[])
{
    FreeType::getInstance().init();

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
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Teste
    Font* font = ResourceManager::getInstance().loadFont("fontuda", "/usr/share/fonts/truetype/freefont/FreeMono.ttf", 48);

    if(font) {
        std::cout << "deu certo chulapinha" << std::endl;
    }

    // Init Editor
    editor.init();

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        editor.run();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
