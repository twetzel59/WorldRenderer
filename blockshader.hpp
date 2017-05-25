#ifndef BLOCKSHADER_HPP_INCLUDED
#define BLOCKSHADER_HPP_INCLUDED

#include <string>
#include "shader.hpp"
#include "transform.hpp"

class BlockShader : public Shader {
    private:
        GLint m_loc_transform_mat;
    public:
        BlockShader(const std::string &name);
        //BlockShader(const std::string &vertex_file, const std::string &fragment_file);
        ~BlockShader() {}

        BlockShader(const BlockShader &) = delete;
        BlockShader & operator=(const BlockShader &) = delete;
        BlockShader(BlockShader &&) = delete;
        BlockShader & operator=(BlockShader &&) = delete;

        void setTransform(const Transform &transform) override;
};

#endif // BLOCKSHADER_HPP_INCLUDED
