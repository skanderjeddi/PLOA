#pragma once

#include <SFML/Graphics.hpp>

#include "proto/common.hpp"
#include "proto/tile.hpp"

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
        const P& dataStructure() const;
        virtual void rotate(const TileRotation&) = 0;
};

TileEdge oppositeEdge(const TileEdge&);