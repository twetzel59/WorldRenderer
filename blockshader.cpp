#include "blockshader.hpp"

BlockShader::BlockShader(const std::string &vertex_file, const std::string &fragment_file) {
    loadFromFiles(vertex_file, fragment_file);

    bindAttribLocation(0, "pos");

    link();
}

void BlockShader::bindAttribLocation(GLuint index, const std::string &name) {
    glBindAttribLocation(m_program_id, 0, "pos");
}
