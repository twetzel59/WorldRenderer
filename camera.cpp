#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

void Camera::calcualateView() {
    m_view_mat = glm::mat4(1.0f);

    m_view_mat = glm::translate(m_view_mat, m_transform.pos);

    m_view_mat = glm::rotate(m_view_mat, m_transform.rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_view_mat = glm::rotate(m_view_mat, m_transform.rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::calculateProjection(float aspect) {
    //m_projection_mat = glm::mat4(1.0f);
    m_projection_mat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::update() {
    calcualateView();
}
