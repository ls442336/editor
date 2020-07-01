#include "openglprimitiverenderer.h"

#include <iostream>
#include "glad.h"
#include <glm/gtc/matrix_transform.hpp>

OpenglPrimitiveRenderer::OpenglPrimitiveRenderer()
{
}

OpenglPrimitiveRenderer::OpenglPrimitiveRenderer(Shader *shader, float width, float height)
{
    this->shader = shader;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    projection = glm::ortho(0.0f, width, height, 0.0f);
}

void OpenglPrimitiveRenderer::drawRect(float x, float y, float width, float height, glm::vec3 color)
{
    if (shader)
    {
        shader->use();
        shader->setMatrix4f("projection", projection);
        shader->setVector3f("primitiveColor", color);
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float quad[] = {
        x, y,
        x + width, y,
        x, y + height,
        x + width, y,
        x, y + height,
        x + width, y + height
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 12, quad);

    glDrawArrays(GL_TRIANGLES, 0, 12);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}