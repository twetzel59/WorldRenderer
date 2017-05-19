#ifndef BLOCKSHADER_HPP_INCLUDED
#define BLOCKSHADER_HPP_INCLUDED

#include <string>
#include "shader.hpp"

class BlockShader : public Shader {
    public:
        BlockShader(const std::string &name);
        //BlockShader(const std::string &vertex_file, const std::string &fragment_file);
        ~BlockShader() {}

        BlockShader(const BlockShader &) = delete;
        BlockShader & operator=(const BlockShader &) = delete;
        BlockShader(BlockShader &&) = delete;
        BlockShader & operator=(BlockShader &&) = delete;
};

#endif // BLOCKSHADER_HPP_INCLUDED
