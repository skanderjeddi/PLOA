#pragma once

#include "proto/carcassonne.hpp"

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"

/**
 * @brief A tile for the Dominos game.
 * 
 */
class CarcassonneTile : virtual public Tile<std::pair<CarcassoneTileType, std::vector<CarcassonePawnType, CarcassonePawnPlacement>>> {
    public:
        CarcassonneTile();
        CarcassonneTile(const std::pair<CarcassoneTileType, std::vector<CarcassonePawnType, CarcassonePawnPlacement>>&);
        CarcassonneTile(const CarcassonneTile&);
        void rotate(const TileRotation&);
};

/**
 * @brief A board for the Dominos game.
 * 
 */
class CarcassoneBoard : virtual public Board<CarcassonneTile> {
    public:
        CarcassoneBoard(BoardProperties&);
        bool canSet(const CarcassonneTile&, const std::pair<int, int>&) const;
        int handleTile(const CarcassonneTile&, const std::pair<int, int>&);
};

/**
 * @brief A user interface for the Dominos game.
 * 
 */
class CarcassoneInterface : virtual public UserInterface<CarcassoneBoard, CarcassonneTile> {
    public:
        CarcassoneInterface(UserInterfaceProperties&, BoardProperties&);
        void draw(CarcassoneBoard&);
        void drawBoard(CarcassoneBoard&, const sf::Vector2i& = sf::Vector2i(0, 0));
        void drawTile(CarcassoneBoard&, const sf::Vector2i&, const sf::Vector2i& = sf::Vector2i(0, 0));
};

/**
 * @brief The Dominos game.
 * 
 */
class Carcassonne : virtual public Game<CarcassonneTile, CarcassoneBoard, CarcassoneInterface> {
    public:
        Carcassonne(UserInterfaceProperties, BoardProperties);
        void drawMainGame();
        void drawGameOver();
        void handleEvent(const sf::Event&, sf::RenderWindow*);
        void run();
};