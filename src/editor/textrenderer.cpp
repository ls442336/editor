#include "textrenderer.h"

#include "glad.h"
#include <glm/gtc/matrix_transform.hpp>

#include "character.h"

TextRenderer::TextRenderer()
    : TextRenderer(nullptr, 0.0f, 0.0f)
{
}

TextRenderer::TextRenderer(Shader *shader, float width, float height)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 6, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->shader = shader;

    if (this->shader)
    {
        this->shader->use();
        this->shader->setMatrix4f("projection", glm::ortho(0.0f, width, height, 0.0f));
    }
}

void TextRenderer::renderText(
    const std::string &text,
    float x,
    float y,
    glm::vec3 color,
    Font *font,
    float size)
{
    if (shader)
    {
        shader->use();
        shader->setVector3f("textColor", color);
    }
    else
    {
        std::cout << "TextRenderer::error: invalid shader" << std::endl;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    if (!font)
    {
        std::cout << "TextRenderer::error: invalid font" << std::endl;
        return;
    }

    for (int i = 0; i < text.size(); i++)
    {

        Character *character = font->getChar((int) text[i]);

        if (!character)
            continue;

        float scale = size / font->size;

        float w = character->size.x * scale;
        float h = character->size.y * scale;

        float posx = x + character->bearing.x * scale;
        float posy = y - character->bearing.y * scale;

        float vertices[] = {
            posx, posy, 0, 0,
            posx + w, posy, 1, 0,
            posx + w, posy + h, 1, 1,
            posx, posy, 0, 0,
            posx + w, posy + h, 1, 1,
            posx, posy + h, 0, 1
        };

        glBindTexture(GL_TEXTURE_2D, character->tex.id);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (character->advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}