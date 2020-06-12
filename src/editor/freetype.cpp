#include "freetype.h"

#include <iostream>

FreeType::FreeType() 
{

}

void FreeType::init()
{
    if(FT_Init_FreeType(&ftLibrary)) {
        std::cout << "Couldn't init FreeType library" << std::endl;
    }
}