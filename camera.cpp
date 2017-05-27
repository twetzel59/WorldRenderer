#include "camera.hpp"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

void Camera::calcualateView() {
    m_view_mat = glm::mat4(1.0f);

    m_view_mat = glm::rotate(m_view_mat, -m_transform.rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    m_view_mat = glm::rotate(m_view_mat, -m_transform.rot.y, glm::vec3(0.0f, 1.0f, 0.0f));

    m_view_mat = glm::translate(m_view_mat, -m_transform.pos);
}

void Camera::calculateProjection(float aspect) {
    //m_projection_mat = glm::mat4(1.0f);
    m_projection_mat = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
}

void Camera::update() {
    calcualateView();
}

void Camera::rotateXY(float x, float y, bool clamp_x) {
    m_transform.rot.x += x;
    m_transform.rot.y += y;

    if(clamp_x) {
        if(m_transform.rot.x > glm::radians(90.0f)) {
            m_transform.rot.x = glm::radians(90.0f);
        } else if(m_transform.rot.x < glm::radians(-90.0f)) {
            m_transform.rot.x = glm::radians(-90.0f);
        }
    }
}

void Camera::moveY(float height_offset) {
    m_transform.pos.y += height_offset;
}

void Camera::moveForward(float forward_offset) {
    m_transform.pos.x += std::sin(m_transform.rot.y) * forward_offset;
    m_transform.pos.z += std::cos(m_transform.rot.y) * forward_offset;
}

void Camera::moveRight(float right_offset) {
    m_transform.pos.x += std::sin(m_transform.rot.y + glm::radians(90.0f)) * right_offset;
    m_transform.pos.z += std::cos(m_transform.rot.y + glm::radians(90.0f)) * right_offset;
}
