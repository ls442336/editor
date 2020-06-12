#ifndef __SHADER__H__
#define __SHADER__H__

#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

/*
* Based on: https://github.com/JoeyDeVries/LearnOpenGL/blob/master/src/7.in_practice/3.2d_game/0.full_source/shader.cpp
*/

class Shader 
{
private:
public:
    unsigned int id;

    void use();
    void compile(const char* vertexSource, const char *fragmentSource);
    void setVector2f(const char* name, const glm::vec2 &value);
    void setVector3f(const char* name, const glm::vec3 &value);
    void setVector4f(const char* name, const glm::vec4 &value);
    void setMatrix3f(const char* name, const glm::mat3 &value);
    void setMatrix4f(const char* name, const glm::mat4 &value);
    void checkCompileErrors(unsigned int id, const std::string& type);
};

#endif  //!__SHADER__H__