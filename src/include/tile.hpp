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
        virtual void draw(sf::RenderWindow&, const sf::Vector2i&, const sf::Vector2i&) = 0;
};