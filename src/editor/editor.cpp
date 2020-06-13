#include "editor.h"
#include <iostream>

#include "config.h"

Editor::Editor()
    : resourceManager(ResourceManager::getInstance())
{

}

void Editor::init()
{
    // init settings
    settings.width = config::window::width;
    settings.height = config::window::height;

    // Load shaders
    Shader* textShader = resourceManager.loadShader("text", "data/shaders/text.vs", "data/shaders/text.fs");

    // Load fonts
    resourceManager.loadFont("ubuntu", "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 100);

    // Initialize renderers
    textRenderer = std::make_unique<TextRenderer>(textShader, (float)settings.width, (float)settings.height);

}

void Editor::run()
{
    textRenderer->renderText("aAAAAAAAA", 0, 48, glm::vec3(1, 1, 1), resourceManager.getFont("ubuntu"), 48);
}