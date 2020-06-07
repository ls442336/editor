#include "fileutil.h"
#include <fstream>

std::string FileUtil::read(std::string path) 
{

    std::ifstream file;

    file.open(path);
    std::string output((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    file.close();

    return output;
}