#ifndef CHUNK_HPP_INCLUDED
#define CHUNK_HPP_INCLUDED

#include <array>
#include <string>
#include <vector>
#include "glad/glad.h"
//#include "blocks.hpp"
#include "blockshader.hpp"
#include "dynamicexception.hpp"
#include "entity.hpp"
#include "model.hpp"
#include "node.hpp"
#include "texture.hpp"

class Chunk /* final */ {
    private:
        static constexpr int k_chunk_size    = 8;
        static constexpr int k_chunk_size_sq = k_chunk_size * k_chunk_size;
        static constexpr int k_chunk_size_cb = k_chunk_size_sq * k_chunk_size;

        std::array<Node, k_chunk_size_cb> m_blocks;

        Model *m_model;
        Entity *m_entity;

        int index(int x, int y, int z) const;
        Node & blockAt(int x, int y, int z);
        const Node & blockAt(int x, int y, int z) const;
        /* void generateGeometry(std::vector<GLuint> &indices,
                              std::vector<GLfloat> &positions,
                              std::vector<GLfloat> &colors,
                              std::vector<GLfloat> &uv);
        */
    public:
        class UninitializedChunkException : public DynamicException {
            public:
                UninitializedChunkException(const std::string &msg) : DynamicException(msg) {}
        };

        /*
        Chunk(const Texture &tex, int chunk_x, int chunk_y, int chunk_z);
        Chunk(const Texture &tex) : Chunk(tex, 0, 0, 0) {}
        */
        Chunk();
        ~Chunk();

        Chunk(const Chunk &) = delete;
        Chunk & operator=(const Chunk &) = delete;
        Chunk(Chunk &&) = delete;
        Chunk & operator=(Chunk &&) = delete;

        void generateGeometry(const Texture &tex, int chunk_x, int chunk_y, int chunk_z);
        void draw(BlockShader &shader);
};

#endif // CHUNK_HPP_INCLUDED
