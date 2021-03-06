#include "texture.hpp"
#include <iostream>
#include <vector>
#include "lodepng/lodepng.h"

Texture::Texture(const std::string &filename) {
    std::vector<unsigned char> pixels;
    unsigned error = lodepng::decode(pixels, m_width, m_height, std::string("res/") + filename + ".png");
    if(error) {
        throw TextureLoadException(lodepng_error_text(error));
    }

    /*
    for(unsigned char i : pixels) {
        std::cout << "pixel: " << (int)i << std::endl;
    }
    */

    createGlTexture(pixels, m_width, m_height);
}

Texture::~Texture() {
    std::cout << "tex: " << m_id << std::endl;
    //Ok if 0
    glDeleteTextures(1, &m_id);
}

Texture::Texture(Texture &&rhs)
    :   m_id(rhs.m_id)
{
    rhs.m_id = 0;
}

void Texture::createGlTexture(const std::vector<unsigned char> &pixels, unsigned width, unsigned height) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glBindTexture(GL_TEXTURE_2D, 0);
}
