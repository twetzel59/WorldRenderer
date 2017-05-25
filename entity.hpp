#ifndef ENTITY_HPP_INCLUDED
#define ENTITY_HPP_INCLUDED

#include "model.hpp"
#include "shader.hpp"
#include "transform.hpp"

class Entity {
    private:
        const Model &m_model;
        Transform m_transform;
    public:
        Entity(const Model &model);
        virtual ~Entity() {}

        Entity(const Entity &) = delete;
        Entity & operator=(const Entity &) = delete;
        Entity(Entity &&) = delete;
        Entity & operator=(Entity &&) = delete;

        inline const Model & getModel() const { return m_model; }
        inline const Transform & getTransform() const { return m_transform; }

        inline void setTransform(const Transform &transform) { m_transform = transform; }

        void draw(Shader &shader) const;
};

#endif // ENTITY_HPP_INCLUDED
