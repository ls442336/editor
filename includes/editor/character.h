#ifndef __CHARACTER__H__
#define __CHARACTER__H__

#include <glm/glm.hpp>

#include "texture2d.h"

class Character {
public:
    Character();
    
    Texture2D tex;
    glm::vec2 size;
    glm::vec2 bearing;
    unsigned int advance;
};

#endif  //!__CHARACTER__H__