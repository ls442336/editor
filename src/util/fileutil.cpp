#include "fileutil.h"
#include <fstream>

#include "freetype.h"

std::string FileUtil::read(const std::string& path) 
{

    std::ifstream file;

    file.open(path);

    if(!file.is_open())
    {
        throw std::runtime_error("Couldn't load file " + path);
    }

    std::string output((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    file.close();

    return output;
}

unsigned char* FileUtil::loadImage(const std::string& path)
{
    int width, height, channels;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if(!data) {
        throw std::runtime_error("Couldn't load image " + path);
    }

    return data;
}

FT_Face FileUtil::loadFont(const std::string& path)
{
    FT_Face face;

    if (FT_New_Face(FreeType::getInstance().ftLibrary, path.c_str(), 0, &face)) 
    {
        throw std::runtime_error("Couldn't load font " + path);
    }

    return face;
}