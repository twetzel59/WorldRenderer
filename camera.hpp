#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glm/mat4x4.hpp>
#include "transform.hpp"

class Camera {
    private:
        Transform m_transform;
        glm::mat4 m_view_mat;
        glm::mat4 m_projection_mat;

        void calcualateView();
        void calculateProjection(float aspect);
    public:
        Camera(float aspect_ratio, const Transform &transform = Transform())
            :   m_transform(transform),
                m_view_mat(1.0f)
        {
            calculateProjection(aspect_ratio);
        }

        void update();
        void rotateXY(float x, float y, bool clamp_y = true);
        void moveY(float height_offset);
        void moveForward(float forward_offset);
        void moveRight(float right_offset);

        inline const Transform & getTransform() const { return m_transform; }
        inline void setTransform(const Transform &transform) { m_transform = transform; }

        inline const glm::mat4 & getViewMatrix() const { return m_view_mat; }
        inline const glm::mat4 & getProjectionMatrix() const { return m_projection_mat; }
};

#endif // CAMERA_HPP_INCLUDED
