#ifndef __TEXTURE2D__H__
#define __TEXTURE2D__H__

class Texture2D
{
public:
    unsigned int id;
    unsigned int width;
    unsigned int height;
    unsigned int internalFormat;
    unsigned int imageFormat;
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMag;

    Texture2D();

    void create(unsigned char *data, unsigned int width, unsigned int height);
    void bind();
};

#endif  //!__TEXTURE__H__