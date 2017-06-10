#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "blocks.hpp"

class Node {
    private:
        BlockId m_id;
    public:
        Node() : m_id(BlockId::Air) {}
        Node(BlockId id) : m_id(id) {}

        inline BlockId getId() const { return m_id; }
};

#endif // NODE_HPP_INCLUDED
