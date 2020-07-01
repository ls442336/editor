#ifndef EDITOR_H
#define EDITOR_H

#include <memory>
#include "glad.h"
#include <GLFW/glfw3.h>

#include "settings.h"
#include "resourcemanager.h"

#include "textrenderer.h"
#include "primitiverenderer.h"

class Editor
{
public:
    Settings settings;
    ResourceManager& resourceManager;
    std::unique_ptr<TextRenderer> textRenderer;
    std::unique_ptr<PrimitiveRenderer> primitiveRenderer;

    std::vector<char> content;
    std::vector<char>::iterator cursor;

    Editor();

    void init();
    void run();

    void loadContentFromString(const std::string& text);
};

#endif