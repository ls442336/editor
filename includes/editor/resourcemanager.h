#ifndef __RESOURCEMANAGER__H__
#define __RESOURCEMANAGER__H__

#include <iostream>
#include <memory>
#include <map>

#include "shader.h"
#include "texture2d.h"

class ResourceManager {
public:
    static ResourceManager& getInstance()
    {
        static ResourceManager instance;
        return instance;
    }
    ResourceManager();

    ResourceManager(ResourceManager const&) = delete;
    void operator=(ResourceManager const&)  = delete;

    std::map<std::string, std::unique_ptr<Shader>> shaders;
    std::map<std::string, std::unique_ptr<Texture2D>> textures2d;
    
    Shader* getShader(const std::string& name);
    Texture2D* getTexture2D(const std::string& name);

    Shader* loadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    Texture2D* loadTexture2D(const std::string& name, const std::string& path, int width, int height);
};

#endif  //!__RESOURCEMANAGER__H__