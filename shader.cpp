#include "shader.hpp"
#include <fstream>
#include <iostream>

Shader::~Shader() {
    stop();
    glDeleteProgram(m_program_id);
}

GLuint Shader::loadShader(const std::string &filename, ShaderType type) {
    std::ifstream file;

    file.open(filename);
    if(!file.good()) {
        throw ShaderLoadException("Failed to open shader " + filename);
    }

    file.seekg(0, file.end);
    if(!file.good()) {
        throw ShaderLoadException("Failed to seek to end of " + filename);
    }

    long filesize = file.tellg();
    if(!file.good()) {
        throw ShaderLoadException("Failed to get position in input sequence");
    }

    file.seekg(0, file.beg);
    if(!file.good()) {
        throw ShaderLoadException("Failed to seek to beginning of shader source");
    }

    std::string src;
    src.resize(filesize);
    src.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    //std::cout << src << std::endl;

    GLuint shader = glCreateShader(static_cast<GLenum>(type));
    const char *c_str_ptr = src.c_str();
    glShaderSource(shader, 1, &c_str_ptr, nullptr);
    glCompileShader(shader);

    GLint result = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE) {
        glDeleteShader(shader);
        throw ShaderLoadException("Failed to compile shader");
    }

    return shader;
}

void Shader::link() {
    glLinkProgram(m_program_id);
    glValidateProgram(m_program_id);

    GLint result = GL_TRUE;
    glGetShaderiv(m_program_id, GL_VALIDATE_STATUS, &result);
    if(result == GL_FALSE) {
        //char buf[2048];
        //int len;
        //glGetProgramInfoLog(m_program_id, 2048, &len, buf);
        //std::cout << buf << std::endl;
        throw ShaderLoadException("Failed to link shader");
    }
}

void Shader::loadFromFiles(const std::string &name) {
//void Shader::loadFromFiles(const std::string &vertex_file, const std::string &fragment_file) {
    const std::string vertex_file(std::string("shaders/" + name + ".vert"));
    const std::string fragment_file(std::string("shaders/" + name + ".frag"));

    GLuint prog = glCreateProgram();
    if(!prog) {
        throw ShaderLoadException("glCreateProgram() -> 0");
    }

    GLuint vertex = loadShader(vertex_file, ShaderType::Vertex);
    GLuint fragment = loadShader(fragment_file, ShaderType::Fragment);

    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);

    glDetachShader(m_program_id, vertex);
    glDetachShader(m_program_id, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    m_program_id = prog;
}

GLint Shader::getUniformLocation(const std::string &name) {
    GLint res = glGetUniformLocation(m_program_id, name.c_str());

    if(res == -1) {
        throw UniformLocationException("Failed to locate or use uniform: " + name);
    }

    return res;
}

void Shader::bindAttribLocation(GLuint index, const std::string &name) {
    glBindAttribLocation(m_program_id, index, name.c_str());
}

void Shader::uniform(GLint location, GLfloat value) {
    glUniform1f(location, value);
}

void Shader::uniform(GLint location, const glm::mat4 &value) {
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

void Shader::start() const {
    glUseProgram(m_program_id);
}

void Shader::stop() const {
    glUseProgram(0);
}
