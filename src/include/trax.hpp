#pragma once

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"

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
};

class TraxBoard : virtual public Board<TraxTile> {
    public:
        TraxBoard();
        TraxBoard(BoardProperties&);
        bool canSet(const TraxTile&, const std::pair<int, int>&) const;
};

class TraxInterface : virtual public UserInterface<TraxBoard, TraxTile> {
    public:
        TraxInterface(UserInterfaceProperties&, BoardProperties&);
        void draw(TraxBoard&);
        void drawBoard(TraxBoard&);
        void drawTile(TraxTile&, const sf::Vector2i&);
        void handleEvent(const sf::Event&);
};

class Trax : virtual public Game<TraxTile, TraxBoard, TraxInterface> {
    public:
        Trax(UserInterfaceProperties);
        void run();
};