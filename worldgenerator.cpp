#include "worldgenerator.hpp"

extern "C" {
    #include "noise/noise.h"
}

namespace wg {
    void generate(Chunk &chunk, int cx, int cy, int cz) {
        for(int x = 0; x < Chunk::k_chunk_size; ++x) {
            for(int y = 0; y < Chunk::k_chunk_size; ++y) {
                for(int z = 0; z < Chunk::k_chunk_size; ++z) {
                    //These are the world coords, calculated from chunk coords.
                    const int wx = Chunk::k_chunk_size * cx + x;
                    const int wy = Chunk::k_chunk_size * cy + y;
                    const int wz = Chunk::k_chunk_size * cz + z;

                    if(wy < 8) {
                        chunk.setBlock(x, y, z, BlockId::Soil);
                    } else {
                        if(wy < 11 + simplex2(wx * 0.05, wz * 0.05, 2, 0.3, 2) * 4) {
                            chunk.setBlock(x, y, z, BlockId::Grass);
                        }
                    }
                }
            }
        }
    }
}
