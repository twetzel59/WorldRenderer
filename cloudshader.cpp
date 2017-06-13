#include "cloudshader.hpp"

CloudShader::CloudShader() {

    loadFromFiles("cloud");

    bindAttribLocation(0, "pos");
    bindAttribLocation(1, "uv");

    link();

    m_loc_transform_mat = getUniformLocation("transform_mat");
    m_loc_projection_mat = getUniformLocation("projection_mat");
    m_loc_view_mat = getUniformLocation("view_mat");
    m_loc_sky_color = getUniformLocation("sky_color");
    //m_loc_daylight = getUniformLocation("daylight");

}

void CloudShader::setTransform(const glm::mat4 &transform) {
    uniform(m_loc_transform_mat, transform);
}

void CloudShader::setProjection(const glm::mat4 &projection) {
    uniform(m_loc_projection_mat, projection);
}

void CloudShader::setView(const glm::mat4 &view) {
    glm::mat4 no_translate(view);

    no_translate[3][0] = 0.0f; // no x transform
    no_translate[3][2] = 0.0f; // no z transform

    uniform(m_loc_view_mat, no_translate);
}

void CloudShader::setSkyColor(const glm::vec3 &color) {
    uniform(m_loc_sky_color, color);
}

void CloudShader::setDaylight(float light) {
    /** TODO: what to do about unused method? Remove from parent and push to BlockShader? **/
    //uniform(m_loc_daylight, light);
}
