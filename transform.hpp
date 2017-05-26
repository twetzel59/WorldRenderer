#ifndef TRANSFORM_HPP_INCLUDED
#define TRANSFORM_HPP_INCLUDED

#include <glm/vec3.hpp>

struct Transform {
    glm::vec3 pos;
    glm::vec2 rot;

    Transform(const glm::vec3 &new_pos, const glm::vec2 &new_rot)
        :   pos(new_pos),
            rot(new_rot)
    {}

    Transform()
        :   Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f))
    {}
};

#endif // TRANSFORM_HPP_INCLUDED
