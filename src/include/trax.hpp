#pragma once

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"

#include "trax.hpp"

enum class TraxTileFace {
    HEADS,
    TAILS
};

enum class TraxTileEdge {
    BLACK,
    WHITE
};

class TraxTile : virtual public Tile<std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>> {
    public:
        TraxTile();
        TraxTile(const std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>&);
        TraxTile(const TraxTile&);
        void rotate(const TileRotation&);
        void draw(sf::RenderWindow&, const sf::Vector2i&, const sf::Vector2i&);
};

class TraxBoard : virtual public Board<TraxTile> {
    public:
        TraxBoard();
        TraxBoard(const TraxBoard&);
        void draw(sf::RenderWindow&, const sf::Vector2i&);
};