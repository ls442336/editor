#ifndef __PRIMITIVERENDERER__H__
#define __PRIMITIVERENDERER__H__

#include <glm/glm.hpp>

class PrimitiveRenderer {
public:
    virtual void drawRect(float x, float y, float width, float height, glm::vec3 color) = 0;
};

#endif  //!__PRIMITIVERENDERER__H__