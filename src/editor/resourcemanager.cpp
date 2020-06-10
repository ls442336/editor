#include "resourcemanager.h"

#include "fileutil.h"

ResourceManager::ResourceManager()
{
    
}

Shader* ResourceManager::getShader(const std::string& name)
{
    if(shaders.find(name) != shaders.end())
    {
        return shaders[name].get();
    }
    
    return nullptr;
}

Texture2D* ResourceManager::getTexture2D(const std::string& name) 
{
    if(textures2d.find(name) != textures2d.end())
    {
        return textures2d[name].get();
    }
    
    return nullptr;
}

Shader* ResourceManager::loadShader (const std::string& name,
                    const std::string& vertexShaderPath,
                    const std::string& fragmentShaderPath)
{
    // Check if resource with this name was allocated
    if(getShader(name) != nullptr) {
        return nullptr;
    }

    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    // Try to read the files
    try{
        vertexShaderSource = FileUtil::read(vertexShaderPath);
        fragmentShaderSource = FileUtil::read(fragmentShaderPath);
    }catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return nullptr;
    }

    std::unique_ptr<Shader> shader = std::make_unique<Shader>();

    // Try compile the shaders from source
    try{
        shader->compile(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        return nullptr;
    }

    Shader *shaderCreated = shader.get();
    shaders.insert(std::make_pair(name, std::move(shader)));

    return shaderCreated;
}

Texture2D* ResourceManager::loadTexture2D(const std::string& name, const std::string& path, int width, int height)
{
    unsigned char *data = nullptr;

    try{
        data = FileUtil::loadImage(path);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }

    std::unique_ptr<Texture2D> texture2d = std::make_unique<Texture2D>();
    
    texture2d->create(data, width, height);

    Texture2D* textureCreated = texture2d.get();
    textures2d.insert(std::make_pair(name, std::move(texture2d)));

    delete data;

    return textureCreated;
}