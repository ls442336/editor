#include "shader.h"

void Shader::use()
{
    glUseProgram(id);
}

void Shader::compile(const char *vertexSource, const char* fragmentSource) 
{
    unsigned int vertexShader, fragmentShader;

    // Create and compile vertexShader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    checkCompileErrors(vertexShader, "VERTEX");

    // Create and compile fragmentShader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    checkCompileErrors(fragmentShader, "FRAGMENT");

    // Create and link shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);
    glLinkProgram(this->id);

    checkCompileErrors(this->id, "PROGRAM");

    // Delete vertex and fragment shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::setVector2f(const char* name, const glm::vec2 &value) 
{
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}

void Shader::setVector3f(const char* name, const glm::vec3 &value)
{
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char* name, const glm::vec4 &value)
{
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix3f(const char* name, const glm::mat3 &value)
{
    glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(value));
}

void Shader::setMatrix4f(const char* name, const glm::mat4 &value) 
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(value));
}

void Shader::checkCompileErrors(unsigned int id, const std::string& type) 
{
    char infoLog[512];
    int success;

    if(type == "PROGRAM") 
    {

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            throw std::runtime_error("ERROR: SHADER COMPILATION ERROR:\n" + std::string(infoLog));
        }

    } else
    {
        glGetShaderiv(id, GL_LINK_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            throw std::runtime_error("ERROR: " + type + " SHADER LINK ERROR:\n" + std::string(infoLog));
        }
    }
    
}