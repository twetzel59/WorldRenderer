#ifndef BLOCKS_HPP_INCLUDED
#define BLOCKS_HPP_INCLUDED

enum class BlockId {
    Air,
    Soil,
    Grass
};

static constexpr int k_block_id_max = static_cast<int>(BlockId::Grass);

#endif // BLOCKS_HPP_INCLUDED
