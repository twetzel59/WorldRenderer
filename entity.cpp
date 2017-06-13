#include "entity.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Entity::draw(Shader &shader, bool translate_x, bool translate_y, bool translate_z) const {
    //shader.start();

    glm::mat4 trans_mat = glm::mat4(1.0f);

    if(translate_x || translate_y || translate_z) {
        trans_mat = glm::translate(trans_mat, glm::vec3(translate_x ? m_transform.pos.x : 0.0f,
                                                        translate_y ? m_transform.pos.y : 0.0f,
                                                        translate_z ? m_transform.pos.z : 0.0f));
    }

    trans_mat = glm::rotate(trans_mat, m_transform.rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
    trans_mat = glm::rotate(trans_mat, m_transform.rot.y, glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setTransform(trans_mat);

    m_model.draw();

    //shader.stop();
}
