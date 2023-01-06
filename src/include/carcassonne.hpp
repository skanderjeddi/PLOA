#pragma once

#include "proto/carcassonne.hpp"
#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"
#include "dominos.hpp"

#define CARCASSONNE_TILE_SIZE 85
#define CARCASSONNE_BOARD_WIDTH 9
#define CARCASSONNE_BOARD_HEIGHT 9
#define CARCASSONNE_WINDOW_WIDTH (CARCASSONNE_BOARD_WIDTH * CARCASSONNE_TILE_SIZE) + 2 * DOMINOS_TILE_SIZE
#define CARCASSONNE_WINDOW_HEIGHT (CARCASSONNE_BOARD_HEIGHT * CARCASSONNE_TILE_SIZE) + 2 * DOMINOS_TILE_SIZE

enum class CarcassonneTileGrid
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_CENTER,
    MIDDLE_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

enum class CarcassonneTileType
{
    ROAD,
    CITY,
    FIELD,
    MONASTERY
};

enum class CarcassonnePawnType
{
    KNIGHT,
    MONK,
    PEASANT,
    THIEF
};

enum class CarcassonnePawnPlacement
{
    CENTER,
    CORNER,
    EDGE
};

enum class CarcassonnePawnColor
{
    RED,
    BLUE,
    YELLOW,
    GREEN
};

struct CarcassonnePawn
{
    CarcassonnePawnType type;
    CarcassonnePawnColor color;
};

/**
 * @brief A tile for the Dominos game.
 *
 */
class CarcassonneTile : virtual public Tile<std::map<TileEdge, CarcassonneTileType>>
{
protected:
    int textureId;
    int rotationAngle = 0;
    std::map<CarcassonneTileGrid,
             CarcassonneTileType>
        grid;
    std::vector<std::pair<CarcassonnePawn,
                          CarcassonneTileGrid>>
        pawns;

public:
    CarcassonneTile();
    CarcassonneTile(int);
    CarcassonneTile(const CarcassonneTile &);
    void rotate(const TileRotation &);
    void setEdges(CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType);
    void setGrid(CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType, CarcassonneTileType);
    void setPawn(CarcassonnePawn, CarcassonneTileGrid);
    bool hasCenter() const;
    bool hasMonastery() const;
    std::vector<std::pair<CarcassonnePawn,
                          CarcassonneTileGrid>>
    getPawns() const
    {
        return pawns;
    }
    std::map<CarcassonneTileGrid,
             CarcassonneTileType>
    getGrid() const
    {
        return grid;
    };
    int getTextureId() const
    {
        return textureId;
    };
    int getRotationAngle() const
    {
        return rotationAngle;
    };
};

/**
 * @brief A board for the Dominos game.
 *
 */
class CarcassonneBoard : virtual public Board<CarcassonneTile>
{
public:
    CarcassonneBoard(BoardProperties &);
    bool canSet(const CarcassonneTile &,
                const std::pair<int, int> &) const;
    int handleTile(const CarcassonneTile &,
                   const std::pair<int, int> &);
    bool isCityClosed(const CarcassonneTile &,
                      const std::pair<int, int> &);
    int isCityClosedRecursive(std::vector<std::pair<int, int>>,
                              const CarcassonneTile &,
                              const std::pair<int, int> &);
    bool hasMonastery(const CarcassonneTile &,
                      const std::pair<int, int> &position, std::map<int, std::pair<std::string, int>> &, std::map<std::string, CarcassonnePawnColor>);
    bool isMonasteryClosed(const CarcassonneTile &,
                           const std::pair<int, int> &, std::map<int, std::pair<std::string, int>> &, std::map<std::string, CarcassonnePawnColor>);
    bool isRoadFinished(const CarcassonneTile &,
                        const std::pair<int, int> &, std::map<int, std::pair<std::string, int>> &, std::map<std::string, CarcassonnePawnColor>);
    int isRoadFinishedRecursive1(const CarcassonneTile &,
                                 const std::pair<int, int> &,
                                 const std::pair<int, int> &, std::map<int, std::pair<std::string, int>> &, std::map<std::string, CarcassonnePawnColor>);
    bool isRoadFinishedRecursive2(int,
                                  const CarcassonneTile &,
                                  const std::pair<int, int> &,
                                  const std::pair<int, int> &, std::map<CarcassonnePawnColor, int> &, std::map<int, std::pair<std::string, int>> &, std::map<std::string, CarcassonnePawnColor>);
};

/**
 * @brief A user interface for the Dominos game.
 *
 */
class CarcassonneInterface : virtual public UserInterface<CarcassonneBoard, CarcassonneTile>
{
protected:
    sf::Texture tileSet;

public:
    CarcassonneInterface(UserInterfaceProperties &, BoardProperties &);
    void draw(CarcassonneBoard &);
    void drawBoard(CarcassonneBoard &,
                   const sf::Vector2i & = sf::Vector2i(0, 0));
    void drawTile(CarcassonneTile &,
                  const sf::Vector2i &,
                  const sf::Vector2i & = sf::Vector2i(0, 0));
};

/**
 * @brief The Dominos game.
 *
 */
class Carcassonne : virtual public Game<CarcassonneTile, CarcassonneBoard, CarcassonneInterface>
{
protected:
    std::vector<CarcassonneTile *> tiles;
    bool isPlacingPawn = false;
    std::map<std::string,
             CarcassonnePawnColor>
        playerColors;
    int currentTileX,
        currentTileY;

public:
    Carcassonne(UserInterfaceProperties, BoardProperties);
    void drawGameScreen();
    void drawGameOverScreen();
    void handleEvent(const sf::Event &, sf::RenderWindow *);
    void handlePawnPlacement(sf::RenderWindow *);
    void registerPlayer(const std::string &name, CarcassonnePawnColor color)
    {
        scoreboard[scoreboard.size()] = std::make_pair(name, 0);
        playerColors[name] = color;
    }
};