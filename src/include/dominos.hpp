#pragma once

#include "proto/dominos.hpp"

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"

#define DOMINOS_TILE_SIZE 85
#define DOMINOS_BOARD_WIDTH 10
#define DOMINOS_BOARD_HEIGHT 10
#define DOMINOS_WINDOW_WIDTH (DOMINOS_BOARD_WIDTH + 2) * DOMINOS_TILE_SIZE
#define DOMINOS_WINDOW_HEIGHT (DOMINOS_BOARD_HEIGHT + 1) * DOMINOS_TILE_SIZE

/**
 * @brief A tile for the Dominos game.
 * 
 */
class DominosTile : virtual public Tile<std::map<TileEdge, std::vector<int>>> {
    public:
        DominosTile();
        DominosTile(const std::map<TileEdge, std::vector<int>>&);
        DominosTile(const DominosTile&);
        void rotate(const TileRotation&);
};

/**
 * @brief A board for the Dominos game.
 * 
 */
class DominosBoard : virtual public Board<DominosTile> {
    public:
        DominosBoard(BoardProperties&);
        bool canSet(const DominosTile&, const std::pair<int, int>&) const;
        int handleTile(const DominosTile&, const std::pair<int, int>&);
};

/**
 * @brief A user interface for the Dominos game.
 * 
 */
class DominosInterface : virtual public UserInterface<DominosBoard, DominosTile> {
    public:
        DominosInterface(UserInterfaceProperties&, BoardProperties&);
        void draw(DominosBoard&);
        void drawBoard(DominosBoard&, const sf::Vector2i& = sf::Vector2i(0, 0));
        void drawTile(DominosTile&, const sf::Vector2i&, const sf::Vector2i& = sf::Vector2i(0, 0));
};

/**
 * @brief The Dominos game.
 * 
 */
class Dominos : virtual public Game<DominosTile, DominosBoard, DominosInterface> {
    private:
        int remainingTiles;
    public:
        Dominos(UserInterfaceProperties, BoardProperties, int);
        void drawGameScreen();
        void drawGameOverScreen();
        void handleEvent(const sf::Event&, sf::RenderWindow*);
};