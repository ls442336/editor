#include "font.h"

Font::Font()
{

}

Font::Font(float size)
{
    this->size = size;
}

Character* Font::getChar(int character)
{
    if(character < characters.size()){
        return characters[character].get();
    }

    return nullptr;
}