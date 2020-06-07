#include "texture2d.h"

#include "glad.h"


#include <iostream>

Texture2D::Texture2D()
    : internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMag(GL_LINEAR)
{
    glGenTextures(1, &this->id);

    std::cout << "texture created: " << this->id << std::endl;
}

void Texture2D::create(unsigned char *data, unsigned int width, unsigned int height)
{
    this->width = width;
    this->height = height;
    
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}