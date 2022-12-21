#pragma once

#include "proto/trax.hpp"

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"

/**
 * @brief The Trax tile's face.
 */
enum class TraxTileFace {
    HEADS,
    TAILS
};

/**
 * @brief The Trax tile's edge.
 */
enum class TraxTileEdge {
    BLACK,
    WHITE
};

/**
 * @brief The Trax tile.
 */
class TraxTile : virtual public Tile<std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>> {
    public:
        TraxTile();
        TraxTile(const std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>&);
        TraxTile(const TraxTile&);
        void rotate(const TileRotation&);
};

/**
 * @brief The Trax board.
 */
class TraxBoard : virtual public Board<TraxTile> {
    public:
        TraxBoard();
        TraxBoard(BoardProperties&);
        bool canSet(const TraxTile&, const std::pair<int, int>&) const;
        int handleTile(const TraxTile&, const std::pair<int, int>&);
};

/**
 * @brief The Trax interface.
 */
class TraxInterface : virtual public UserInterface<TraxBoard, TraxTile> {
    public:
        TraxInterface(UserInterfaceProperties&, BoardProperties&);
        void draw(TraxBoard&);
        void drawBoard(TraxBoard&, const sf::Vector2i& = sf::Vector2i(0, 0));
        void drawTile(TraxTile&, const sf::Vector2i&, const sf::Vector2i& = sf::Vector2i(0, 0));
};

/**
 * @brief The Trax game.
 */
class Trax : virtual public Game<TraxTile, TraxBoard, TraxInterface> {
    public:
        Trax(UserInterfaceProperties);
        void handleEvent(const sf::Event&, sf::RenderWindow*);
        void run();
};