#ifndef __OPENGLPRIMITIVERENDERER__H__
#define __OPENGLPRIMITIVERENDERER__H__

#include "primitiverenderer.h"
#include <glm/glm.hpp>
#include "shader.h"

class OpenglPrimitiveRenderer : public PrimitiveRenderer{
public:
    OpenglPrimitiveRenderer();
    OpenglPrimitiveRenderer(Shader *shader, float width, float height);

    unsigned int VBO;
    unsigned int VAO;
    Shader *shader;
    glm::mat4 projection;

    void drawRect(float x, float y, float width, float height, glm::vec3 color);
};

#endif  //!__OPENGLPRIMITIVERENDERER__H__