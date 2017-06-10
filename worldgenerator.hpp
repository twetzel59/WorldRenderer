#ifndef WORLDGENERATOR_HPP_INCLUDED
#define WORLDGENERATOR_HPP_INCLUDED

#include "chunk.hpp"

namespace wg {
    //Generates a chunk based on the coordinates given.
    //These are chunk coords.
    void generate(Chunk &chunk, int cx, int cy, int cz);
}

#endif // WORLDGENERATOR_HPP_INCLUDED
