#include "resourcemanager.h"

#include "fileutil.h"
#include "freetype.h"
#include "character.h"
#include "glad.h"
#include <glm/glm.hpp>

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

Font* ResourceManager::getFont(const std::string& name) 
{
    if(fonts.find(name) != fonts.end())
    {
        return fonts[name].get();
    }
    
    return nullptr;
}

Shader* ResourceManager::loadShader (const std::string& name,
                    const std::string& vertexShaderPath,
                    const std::string& fragmentShaderPath)
{
    // Check if resource with this name was allocated
    if(getShader(name) != nullptr) {
        std::cout << "shader with name " << name << " already exists" << std::endl;
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

        shader->compile(vertexShaderSource.c_str(),
            fragmentShaderSource.c_str());

    }catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        return nullptr;
    }

    Shader *shaderCreated = shader.get();

    shaders.insert(std::make_pair(name, std::move(shader)));
    
    return shaderCreated;
}

Texture2D* ResourceManager::loadTexture2D(
    const std::string& name, 
    const std::string& path,
    int width,
    int height)
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

Font* ResourceManager::loadFont(
    const std::string& name,
    const std::string& path,
    int size)
{
    FT_Face face;

    try{
        face = FileUtil::loadFont(path);
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
        
        return nullptr;
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    std::unique_ptr<Font> font = std::make_unique<Font>(size);
    
    for(unsigned char i = 0; i < 128; i++)
    {
        if(!FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            std::unique_ptr<Character> character = std::make_unique<Character>();
            Texture2D tex;
            
            // Flags for correct representation of the data buffer
            tex.imageFormat = GL_RED;
            tex.internalFormat = GL_RED;
            tex.wrapS = GL_CLAMP_TO_EDGE;
            tex.wrapT = GL_CLAMP_TO_EDGE;
            
            // Create texture
            tex.create(
                face->glyph->bitmap.buffer,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows);

            // Set character settings
            character->tex = tex;
            character->size = glm::vec2(
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows);
            character->bearing = glm::vec2(
                face->glyph->bitmap_left,
                face->glyph->bitmap_top);
            character->advance = face->glyph->advance.x;
            
            font->characters.push_back(std::move(character));
        } else {
            std::unique_ptr<Character> emptyPtr = std::make_unique<Character>();
            font->characters.push_back(std::move(emptyPtr));
        }
    }

    Font* fontCreated = font.get();
    fonts.insert(std::make_pair(name, std::move(font)));

    FT_Done_Face(face);

    return fontCreated;
}