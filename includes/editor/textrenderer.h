#ifndef __TEXTRENDERER__H__
#define __TEXTRENDERER__H__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "font.h"

class TextRenderer {
public:
    Shader* shader;
    glm::mat4 projection;
    unsigned int vbo;
    unsigned int vao;

    TextRenderer();
    TextRenderer(Shader *shader, float width, float height);

    void renderText(const std::string& text, float x, float y, glm::vec3 color, Font* font, float size);
};

#endif  //!__TEXTRENDERER__H__