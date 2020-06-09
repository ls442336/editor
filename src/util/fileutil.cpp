#include "fileutil.h"
#include <fstream>

std::string FileUtil::read(std::string path) 
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