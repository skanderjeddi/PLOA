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
   
        bool operator==(const TraxTile& t) const;
        bool operator!=(const TraxTile& t) const;
        void rotate(const TileRotation&);
        void flip();
       
};

/**
 * @brief The Trax board.
 */
class TraxBoard : virtual public Board<TraxTile> {
    public:
        TraxBoard();
        TraxBoard(BoardProperties&);
        std::pair<int,int> getTilePos(TraxTile& t);
        bool canSet(const TraxTile&, const std::pair<int, int>&) const;
        int handleTile(const TraxTile&, const std::pair<int, int>&);
        bool checkForced( const std::pair<int, int>&);
        bool isEmpty();
        bool putTile(const std::pair<TileEdge, TraxTile>&n1,std::pair<TileEdge, TraxTile>&n2, const std::pair<int, int>&);
        bool isFinishedLoop(const std::pair<int, int>& goal, const TraxTile& tile);
        int isFinishedLoopRec(const std::pair<int, int>& goal, const std::pair<int, int>& origin,  const TraxTile& tile, const std::pair<int, int>& position, const TraxTileEdge& color);
        bool isFinishedBorder();
        int findBorderPath(const std::pair<int, int>& position,const int& a);
        int findBorderPathRec(const std::pair<int, int>& previous, const std::pair<int, int>& position,const int& a, const TraxTileEdge& color );
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
        void drawGameScreen();
        void drawGameOverScreen();
        void handleEvent(const sf::Event&, sf::RenderWindow*);
        void drawPlayers();
        void drawWinner();
};