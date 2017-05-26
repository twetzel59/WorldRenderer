#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <string>
#include <glm/mat4x4.hpp>
#include "glad/glad.h"
#include "dynamicexception.hpp"
#include "transform.hpp"

class Shader {
    private:
        enum class ShaderType : GLenum {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER
        };

        GLuint m_program_id;

        GLuint loadShader(const std::string &filename, ShaderType type);
    protected:
        //void loadFromFiles(const std::string &vertex_file, const std::string &fragment_file);
        void loadFromFiles(const std::string &name);
        void link();
        //void bindAttrib(GLuint index, const std::string &name);
        void bindAttribLocation(GLuint index, const std::string &name);

        GLint getUniformLocation(const std::string &name);
        void uniform(GLint location, GLfloat value);
        void uniform(GLint location, const glm::mat4 &value);
    public:
        class ShaderLoadException : public DynamicException {
            public:
                ShaderLoadException(const std::string &msg) : DynamicException(msg) {}
        };

        class UniformLocationException : public DynamicException {
            public:
                UniformLocationException(const std::string &msg) : DynamicException(msg) {}
        };

        virtual ~Shader() = 0;

        void start() const;
        void stop() const;

        //virtual void setTransform(const Transform &transform) = 0;
        virtual void setTransform(const glm::mat4 &transform) = 0;
        virtual void setProjection(const glm::mat4 &projection) = 0;
        virtual void setView(const glm::mat4 &view) = 0;
};

#endif // SHADER_HPP_INCLUDED
