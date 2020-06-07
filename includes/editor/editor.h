#ifndef EDITOR_H
#define EDITOR_H

#include "glad.h"
#include <GLFW/glfw3.h>

#include "settings.h"

class Editor
{
public:
    Settings settings;

    Editor() {}

    void init();
    void run();
};

#endif