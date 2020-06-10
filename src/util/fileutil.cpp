#include "fileutil.h"
#include <fstream>

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