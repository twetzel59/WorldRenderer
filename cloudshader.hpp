#ifndef CLOUDSHADER_HPP_INCLUDED
#define CLOUDSHADER_HPP_INCLUDED

#include <glm/mat4x4.hpp>
#include "shader.hpp"
#include "transform.hpp"

class CloudShader : public Shader {
    private:
        GLint m_loc_transform_mat;
        GLint m_loc_projection_mat;
        GLint m_loc_view_mat;
        GLint m_loc_sky_color;
        //GLint m_loc_daylight;
    public:
        CloudShader();
        virtual ~CloudShader() {}

        CloudShader(const CloudShader &) = delete;
        CloudShader & operator=(const CloudShader &) = delete;
        CloudShader(CloudShader &&) = delete;
        CloudShader & operator=(CloudShader &&) = delete;

        void setTransform(const glm::mat4 &transform) override;
        void setProjection(const glm::mat4 &projection) override;
        void setView(const glm::mat4 &view) override;
        void setSkyColor(const glm::vec3 &color) override;
        void setDaylight(float light) override;
};

#endif // CLOUDSHADER_HPP_INCLUDED
