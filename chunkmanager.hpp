#ifndef CHUNKMANAGER_HPP_INCLUDED
#define CHUNKMANAGER_HPP_INCLUDED

#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include "blockshader.hpp"
#include "chunk.hpp"
#include "texture.hpp"

class ChunkManager /* final */ {
    private:
        //Chunk m_chunk;
        static constexpr int k_chunks_x = 8;
        static constexpr int k_chunks_y = 1;
        static constexpr int k_chunks_z = 8;

        struct Key {
            std::int64_t x, y, z;

            Key(int new_x, int new_y, int new_z)
                :   x(new_x),
                    y(new_y),
                    z(new_z)
            {}
        };

        friend bool operator==(const Key &, const Key &);

        struct Hasher {
            std::size_t operator()(const Key &key) const {
                /** TODO: IS A BETTER HASH FUNCTION NEEDED? **/
                return  (((std::hash<std::int32_t>()(key.x) ^
                        (std::hash<std::int32_t>()(key.y) << 1)) >> 1) ^
                         (std::hash<std::int32_t>()(key.z) << 1));
            }
        };

        typedef std::unordered_map<Key, Chunk, Hasher> chunk_map_t;
        chunk_map_t m_chunks;
    public:
        ChunkManager(const Texture &tex);
        ~ChunkManager() {}

        ChunkManager(const ChunkManager &) = delete;
        ChunkManager & operator=(const ChunkManager &) = delete;
        ChunkManager(ChunkManager &&) = delete;
        ChunkManager & operator=(ChunkManager &&) = delete;

        void draw(BlockShader &shader);
};

bool operator==(const ChunkManager::Key &l, const ChunkManager::Key &r);

#endif // CHUNKMANAGER_HPP_INCLUDED
