#ifndef __FREETYPE__H__
#define __FREETYPE__H__

#include <ft2build.h>
#include FT_FREETYPE_H

class FreeType {
public:
    static FreeType& getInstance()
    {
        static FreeType instance;
        return instance;
    }

    FreeType();

    FreeType(FreeType const&) = delete;
    void operator=(FreeType const&)  = delete;

    FT_Library ftLibrary;

    void init();
};

#endif  //!__FREETYPE__H__