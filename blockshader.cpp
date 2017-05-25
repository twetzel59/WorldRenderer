#include "blockshader.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

BlockShader::BlockShader(const std::string &name) {

    loadFromFiles(name);

    bindAttribLocation(0, "pos");
    bindAttribLocation(1, "color");
    bindAttribLocation(2, "uv");

    link();

    m_loc_transform_mat = getUniformLocation("transform_mat");
}

void BlockShader::setTransform(const Transform &transform) {
    glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform.pos);

    uniform(m_loc_transform_mat, trans_mat);
}
