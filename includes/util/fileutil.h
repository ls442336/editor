#ifndef __FILEUTIL__H__
#define __FILEUTIL__H__

#include <iostream>
#include "stb_image.h"

class FileUtil
{
public:
    static std::string read(const std::string& path);
    static unsigned char* loadImage(const std::string& path);
};

#endif  //!__FILEUTIL__H__