#include "entity.hpp"

Entity::Entity(const Model &model)
    :   m_model(model)
{
}

void Entity::draw(Shader &shader) const {
    shader.start();

    shader.setTransform(m_transform);

    m_model.draw();

    shader.stop();
}
