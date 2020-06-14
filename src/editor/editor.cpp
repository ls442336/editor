#include "editor.h"
#include <iostream>

#include "config.h"
#include "fileutil.h"

Editor::Editor()
    : resourceManager(ResourceManager::getInstance())
{
}

void Editor::init()
{
    // init settings
    settings.width = config::window::width;
    settings.height = config::window::height;
    settings.fontSize = 14;

    // Load shaders
    Shader *textShader = resourceManager.loadShader("text", "data/shaders/text.vs", "data/shaders/text.fs");

    // Load fonts
    resourceManager.loadFont("ubuntu", "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 100);

    // Initialize renderers
    textRenderer = std::make_unique<TextRenderer>(textShader, (float)settings.width, (float)settings.height);

    try{
        loadContentFromString(FileUtil::read("data/text/alice.txt"));
    }catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Editor::loadContentFromString(const std::string &text)
{
    for (char c : text)
    {
        content.push_back(c);
    }

    cursor = content.end() - 1;
}

void Editor::run()
{
    Font *selectedFont = resourceManager.getFont("ubuntu");

    if (selectedFont)
    {
        float fontSize = settings.fontSize;
        glm::vec2 gridPos(0, fontSize);

        for (int i = 0; i < content.size(); i++)
        {
            if (content[i] == '\n')
            {
                gridPos.x = 0;
                gridPos.y += fontSize;
                continue;
            }

            float scale = (fontSize / selectedFont->size);
            float advance = selectedFont->getChar(content[i])->advance / 64.0;
            float spacing = advance * scale;

            if (gridPos.x + spacing > settings.width)
            {
                gridPos.x = 0;
                gridPos.y += fontSize;
            }

            textRenderer->renderText(
                std::string(1, content[i]),
                gridPos.x,
                gridPos.y,
                glm::vec3(1, 1, 1),
                selectedFont,
                fontSize);

            gridPos.x += spacing;
        }
    }
}