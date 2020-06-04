#ifndef EDITOR_H
#define EDITOR_H

#include "glad.h"
#include <GLFW/glfw3.h>

class Editor {
private:
    GLFWwindow* window;
public:
    Editor() {}

    Editor(GLFWwindow *window) :
        window(window)
    {
        
    }
    
    void init();
    void run();
};

#endif