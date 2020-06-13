#ifndef __FONT__H__
#define __FONT__H__

#include <iostream>
#include <vector>

#include "character.h"
#include <vector>
#include <memory>

class Font {
public:
    Font();
    Font(float size);

    float size;
    
    std::vector<std::unique_ptr<Character>> characters;

    Character* getChar(int character);
};

#endif  //!__FONT__H__