#ifndef BLOCKSHADER_HPP_INCLUDED
#define BLOCKSHADER_HPP_INCLUDED

#include <string>
#include <glm/mat4x4.hpp>
#include "shader.hpp"
#include "transform.hpp"

class BlockShader : public Shader {
    private:
        GLint m_loc_transform_mat;
        GLint m_loc_projection_mat;
        GLint m_loc_view_mat;
    public:
        BlockShader(const std::string &name);
        //BlockShader(const std::string &vertex_file, const std::string &fragment_file);
        ~BlockShader() {}

        BlockShader(const BlockShader &) = delete;
        BlockShader & operator=(const BlockShader &) = delete;
        BlockShader(BlockShader &&) = delete;
        BlockShader & operator=(BlockShader &&) = delete;

        //void setTransform(const Transform &transform) override;
        void setTransform(const glm::mat4 &transform) override;
        void setProjection(const glm::mat4 &projection) override;
        void setView(const glm::mat4 &view) override;

};

#endif // BLOCKSHADER_HPP_INCLUDED
