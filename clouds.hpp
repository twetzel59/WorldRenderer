#ifndef CLOUDS_HPP_INCLUDED
#define CLOUDS_HPP_INCLUDED

#include "cloudshader.hpp"
#include "entity.hpp"
#include "model.hpp"
#include "texture.hpp"

class Clouds /* final */ {
    private:
        static constexpr float k_cloud_distance = 1000.0f;
        static constexpr float k_cloud_tile_size = 20.0f;
        static constexpr float k_cloud_height = 50.0f;

        /** TODO: smart pointers **/

        Entity *m_entity;
        Model *m_model;
    public:
        Clouds(const Texture &tex);
        ~Clouds();

        Clouds(const Clouds &) = delete;
        Clouds & operator=(const Clouds &) = delete;
        Clouds(Clouds &&) = delete;
        Clouds & operator=(Clouds &&) = delete;

        void draw(CloudShader &shader);
};

#endif // CLOUDS_HPP_INCLUDED
