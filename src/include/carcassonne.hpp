#pragma once

#include "proto/carcassonne.hpp"

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"

enum class CarcassonneTileType {
    ROAD,
    CITY,
    FIELD,
    MONASTERY
};

enum class CarcassonnePawnType {
    KNIGHT,
    MONK,
    PEASANT,
    THIEF
};

enum class CarcassonnePawnPlacement {
    CENTER,
    CORNER,
    EDGE
};

/**
 * @brief A tile for the Dominos game.
 * 
 */
class CarcassonneTile : virtual public Tile<std::pair<CarcassonneTileType, std::vector<std::map<CarcassonnePawnType, CarcassonnePawnPlacement>>>> {
    public:
        CarcassonneTile();
        CarcassonneTile(const std::pair<CarcassonneTileType, std::vector<std::map<CarcassonnePawnType, CarcassonnePawnPlacement>>>&);
        CarcassonneTile(const CarcassonneTile&);
        void rotate(const TileRotation&);
};

/**
 * @brief A board for the Dominos game.
 * 
 */
class CarcassonneBoard : virtual public Board<CarcassonneTile> {
    public:
        CarcassonneBoard(BoardProperties&);
        bool canSet(const CarcassonneTile&, const std::pair<int, int>&) const;
        int handleTile(const CarcassonneTile&, const std::pair<int, int>&);
};

/**
 * @brief A user interface for the Dominos game.
 * 
 */
class CarcassonneInterface : virtual public UserInterface<CarcassonneBoard, CarcassonneTile> {
    public:
        CarcassonneInterface(UserInterfaceProperties&, BoardProperties&);
        void draw(CarcassonneBoard&);
        void drawBoard(CarcassonneBoard&, const sf::Vector2i& = sf::Vector2i(0, 0));
        void drawTile(CarcassonneTile&, const sf::Vector2i&, const sf::Vector2i& = sf::Vector2i(0, 0));
};

/**
 * @brief The Dominos game.
 * 
 */
class Carcassonne : virtual public Game<CarcassonneTile, CarcassonneBoard, CarcassonneInterface> {
    public:
        Carcassonne(UserInterfaceProperties, BoardProperties);
        void drawGameScreen();
        void drawGameOverScreen();
        void handleEvent(const sf::Event&, sf::RenderWindow*);
        void run();
};