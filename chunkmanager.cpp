#include "chunkmanager.hpp"
#include "worldgenerator.hpp"
#include <iostream>

ChunkManager::ChunkManager(const Texture &tex) {
    /** TODO: VERY TEMPORARY **/

    /*
    {
        auto result = m_chunks.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(0, -1, 0), std::forward_as_tuple());
        if(result.second) {
            std::cout << "result.second" << std::endl;
            wg::generate(result.first->second, 0, -1, 0);
            result.first->second.generateGeometry(tex, 0, -1, 0);
        } else {
            std::cout << "!result.second" << std::endl;
        }
    }

    {
        auto result = m_chunks.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(0, 0, 0), std::forward_as_tuple());
        if(result.second) {
            std::cout << "result.second" << std::endl;
            wg::generate(result.first->second, 0, 0, 0);
            result.first->second.generateGeometry(tex, 0, 0, 0);
        } else {
            std::cout << "!result.second" << std::endl;
        }
    }

    {
        auto result = m_chunks.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(0, 1, 0), std::forward_as_tuple());
        if(result.second) {
            std::cout << "result.second" << std::endl;
            wg::generate(result.first->second, 0, 1, 0);
            result.first->second.generateGeometry(tex, 0, 1, 0);
        } else {
            std::cout << "!result.second" << std::endl;
        }
    }

    {
        auto result = m_chunks.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(0, 2, 0), std::forward_as_tuple());
        if(result.second) {
            std::cout << "result.second" << std::endl;
            wg::generate(result.first->second, 0, 2, 0);
            result.first->second.generateGeometry(tex, 0, 2, 0);
        } else {
            std::cout << "!result.second" << std::endl;
        }
    }
    */

    //The loop counters are in chunk coords.
    /*
    for(int cx = -k_chunks_x / 2; cx < k_chunks_x / 2; ++cx) {
        for(int cy = -k_chunks_y / 2; cy < k_chunks_y / 2; ++cy) {
            for(int cz = -k_chunks_z / 2; cz < k_chunks_z / 2; ++cz) {
    */
    for(int cx = 0; cx < k_chunks_x; ++cx) {
        for(int cy = 0; cy < k_chunks_y; ++cy) {
            for(int cz = 0; cz < k_chunks_z; ++cz) {
                auto result = m_chunks.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(cx, cy, cz),
                                 std::forward_as_tuple());
                wg::generate(result.first->second, cx, cy, cz);
                result.first->second.generateGeometry(tex, cx, cy, cz);
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
