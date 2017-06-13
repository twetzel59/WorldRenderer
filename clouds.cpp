#include "clouds.hpp"

Clouds::Clouds(const Texture &tex) {
    m_model = new Model(
        {
            0, 1, 2,
            3, 0, 2
        },

        {
            -k_cloud_distance,  0.0f,   -k_cloud_distance,
            k_cloud_distance,   0.0f,   -k_cloud_distance,
            k_cloud_distance,   0.0f,   k_cloud_distance,
            -k_cloud_distance,  0.0f,   k_cloud_distance,
        },

        {
            0.0f,               k_cloud_tile_size,
            k_cloud_tile_size,  k_cloud_tile_size,
            k_cloud_tile_size,  0.0f,
            0.0f,               0.0f
        },

        tex
    );

    m_entity = new Entity(*m_model, Transform(glm::vec3(0.0f, k_cloud_height, 0.0f), glm::vec2(0.0f, 0.0f)));
}

Clouds::~Clouds() {
    delete m_entity;
    delete m_model;
}

void Clouds::draw(CloudShader &shader) {
    m_entity->draw(shader);
}
