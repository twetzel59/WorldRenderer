#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include <string>
#include <vector>
#include "dynamicexception.hpp"
#include "glad/glad.h"

class Texture /* final */ {
    private:
        GLuint m_id;
        unsigned m_width, m_height;

        void createGlTexture(const std::vector<unsigned char> &pixels, unsigned width, unsigned height);
    public:
        class TextureLoadException : public DynamicException {
            public:
                TextureLoadException(const std::string &msg) : DynamicException(msg) {}
        };

        //Texture();
        Texture(const std::string &filename);
        ~Texture();

        Texture(const Texture &) = delete;
        Texture & operator=(const Texture &) = delete;
        Texture(Texture &&rhs);
        Texture & operator=(Texture &&) = delete;

        inline GLuint getId() const { return m_id; }
        inline unsigned getWidth() const { return m_width; }
        inline unsigned getHeight() const { return m_height; }
};

#endif // TEXTURE_HPP_INCLUDED
