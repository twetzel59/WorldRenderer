#include "blockshader.hpp"
#include <iostream>

BlockShader::BlockShader(const std::string &name) {

    loadFromFiles(name);

    bindAttribLocation(0, "pos");
    bindAttribLocation(1, "color");
    bindAttribLocation(2, "uv");

    link();

    m_loc_transform_mat = getUniformLocation("transform_mat");
    m_loc_projection_mat = getUniformLocation("projection_mat");
    m_loc_view_mat = getUniformLocation("view_mat");
}

/*
void BlockShader::setTransform(const Transform &transform) {
    glm::mat4 trans_mat = glm::translate(glm::mat4(1.0f), transform.pos);

    uniform(m_loc_transform_mat, trans_mat);
}
*/

void BlockShader::setTransform(const glm::mat4 &transform) {
    uniform(m_loc_transform_mat, transform);
}

void BlockShader::setProjection(const glm::mat4 &projection) {
    uniform(m_loc_projection_mat, projection);
}

void BlockShader::setView(const glm::mat4 &view) {
    uniform(m_loc_view_mat, view);
}
