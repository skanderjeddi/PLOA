#pragma once

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"

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
        void draw(sf::RenderWindow&, const sf::Vector2i&, const sf::Vector2i&, const sf::Font&);
};

class TraxBoard : virtual public Board<TraxTile> {
    public:
        TraxBoard();
        TraxBoard(const TraxBoard&);
        bool canSet(const TraxTile&, const std::pair<int, int>&) const;
        void draw(sf::RenderWindow&, const sf::Vector2i&, const sf::Font&);
};

class TraxInterface : virtual public UserInterface<TraxBoard> {
    public:
        TraxInterface(const TraxBoard&, const sf::Vector2i&);
        void draw();
        void handleEvent(const sf::Event&);
};