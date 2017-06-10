#include "chunkmanager.hpp"

ChunkManager::ChunkManager(const Texture &tex) {
    for(int x = 0; x < k_chunks_x; ++x) {
        for(int y = 0; y < k_chunks_y; ++y) {
            for(int z = 0; z < k_chunks_z; ++z) {
                auto result = m_chunks.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(x, y, z),
                                 std::forward_as_tuple());
                result.first->second.generateGeometry(tex, x, y, z);
            }
        }
    }
}

void ChunkManager::draw(BlockShader &shader) {
    //m_chunk.draw(shader);
    for(auto &i : m_chunks) {
        i.second.draw(shader);
    }
}

bool operator==(const ChunkManager::Key &l, const ChunkManager::Key &r) {
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}
