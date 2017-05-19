#include "texture.hpp"
#include <iostream>
#include <vector>
#include "lodepng/lodepng.h"

Texture::Texture(const std::string &filename) {
    std::vector<unsigned char> pixels;
    unsigned width = 0;
    unsigned height = 0;
    unsigned error = lodepng::decode(pixels, width, height, std::string("res/") + filename + ".png");
    if(error) {
        throw TextureLoadException(lodepng_error_text(error));
    }

    for(unsigned char i : pixels) {
        std::cout << "pixel: " << (int)i << std::endl;
    }

    createGlTexture(pixels, width, height);
}

Texture::~Texture() {
    std::cout << "tex: " << m_id << std::endl;
    glDeleteTextures(1, &m_id);
}

void Texture::createGlTexture(const std::vector<unsigned char> &pixels, unsigned width, unsigned height) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE0, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE0, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    glBindTexture(GL_TEXTURE0, 0);
}
