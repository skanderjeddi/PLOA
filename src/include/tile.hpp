#pragma once

#include "proto/interface.hpp"

enum class TileRotation {
    CLOCKWISE,
    COUNTERCLOCKWISE
};

enum class TileEdge {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};

template <class P> class Tile {
    protected:
        P properties;
    
    public:
        Tile();
        Tile(const P&);
        Tile(const Tile&);
        /**
         * @brief Get the data structure object
         * 
         * @return const P& the data structure
         */
        const P& dataStructure() const;
        /**
         * @brief Rotate the tile.
         *
         * @param rotation the rotation to apply 
         */
        virtual void rotate(const TileRotation&) = 0;
};

/**
 * @brief Get the opposite edge of a given edge.
 * 
 * @return TileEdge the opposite edge
 */
TileEdge oppositeEdge(const TileEdge&);