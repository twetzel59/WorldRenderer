#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <string>
#include "glad/glad.h"
#include "dynamicexception.hpp"

class Shader {
    private:
        enum class ShaderType : GLenum {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER
        };

        GLuint loadShader(const std::string &filename, ShaderType type);
    protected:
        GLuint m_program_id;

        void loadFromFiles(const std::string &vertex_file, const std::string &fragment_file);
        void link();
        //void bindAttrib(GLuint index, const std::string &name);
    public:
        class ShaderLoadException : public DynamicException {
            public:
                ShaderLoadException(const std::string &msg) : DynamicException(msg) {}
        };

        virtual ~Shader() = 0;

        void start();
        void stop();
};

#endif // SHADER_HPP_INCLUDED
