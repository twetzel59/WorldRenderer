#include "entity.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Entity::draw(Shader &shader) const {
    //shader.start();

    glm::mat4 trans_mat = glm::mat4(1.0f);

    trans_mat = glm::translate(trans_mat, m_transform.pos);

    trans_mat = glm::rotate(trans_mat, m_transform.rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    trans_mat = glm::rotate(trans_mat, m_transform.rot.y, glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setTransform(trans_mat);

    m_model.draw();

    //shader.stop();
}
