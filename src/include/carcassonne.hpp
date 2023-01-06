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

enum class CarcassonneTileGrid {
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER_CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

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

enum class CarcassonnePawnColor {
    RED,
    BLUE,
    YELLOW,
    GREEN
};

struct CarcassonnePawn {
    CarcassonnePawnType type;
    CarcassonnePawnColor color;
};

/**
 * @brief A tile for the Dominos game.
 * 
 */
class CarcassonneTile : virtual public Tile<std::map<TileEdge, CarcassonneTileType>> {
    protected:
        int textureId;
        int rotationAngle = 0;
        std::map<CarcassonneTileGrid, CarcassonneTileType> grid;
        std::vector<std::pair<CarcassonnePawn, CarcassonneTileGrid>> pawns;
    public:
        CarcassonneTile();
        CarcassonneTile(int);
        CarcassonneTile(const CarcassonneTile&);
        void rotate(const TileRotation&);
        // Get grid
        std::map<CarcassonneTileGrid, CarcassonneTileType> getGrid() { return grid; };
        // Get texture id
        int getTextureId() const { return textureId; };
        // Get rotation
        int getRotationAngle() const { return rotationAngle; };
        void setEdges(CarcassonneTileType left, CarcassonneTileType top, CarcassonneTileType right, CarcassonneTileType bottom) {
            properties[TileEdge::LEFT] = left;
            properties[TileEdge::TOP] = top;
            properties[TileEdge::RIGHT] = right;
            properties[TileEdge::BOTTOM] = bottom;
        }
        void setGrid(CarcassonneTileType tc, CarcassonneTileType tl, CarcassonneTileType tr, CarcassonneTileType cl, CarcassonneTileType cc, CarcassonneTileType cr, CarcassonneTileType bl, CarcassonneTileType bc, CarcassonneTileType br) {
            grid[CarcassonneTileGrid::TOP_CENTER] = tc;
            grid[CarcassonneTileGrid::TOP_LEFT] = tl;
            grid[CarcassonneTileGrid::TOP_RIGHT] = tr;
            grid[CarcassonneTileGrid::CENTER_LEFT] = cl;
            grid[CarcassonneTileGrid::CENTER_CENTER] = cc;
            grid[CarcassonneTileGrid::CENTER_RIGHT] = cr;
            grid[CarcassonneTileGrid::BOTTOM_LEFT] = bl;
            grid[CarcassonneTileGrid::BOTTOM_CENTER] = bc;
            grid[CarcassonneTileGrid::BOTTOM_RIGHT] = br;
        }
        void setGrid(std::map<CarcassonneTileGrid, CarcassonneTileType> g){
            grid = g; 
        }
        bool hasMonastery() const {
            std::cout<<"dansHas"<<std::endl;
            if (grid.count(CarcassonneTileGrid::CENTER_CENTER)){
                std::cout<<"contient "<<std::endl;
                if(grid.at(CarcassonneTileGrid::CENTER_CENTER) == CarcassonneTileType::MONASTERY){
                return true; 

            } 
            }
            if (!grid.count(CarcassonneTileGrid::CENTER_CENTER)){
                std::cout<<"contientpas"<<textureId<<std::endl;
            }
            
            return false; }
        bool hasCenter() const {
            if (grid.count(CarcassonneTileGrid::CENTER_CENTER)){
                std::cout<<"contient un centre "<<std::endl;
                return true;
            }
            else {
               
                std::cout<<"contient pas de centre"<<std::endl;
                 return false; 
            }
        }

        void setPawn(CarcassonnePawn p, CarcassonneTileGrid tg) {
            std::cout << "Placing pawn on ";
            switch (grid[tg]) {
                case CarcassonneTileType::CITY:
                    p.type = CarcassonnePawnType::KNIGHT;
                    std::cout << " a city";
                    break;
                case CarcassonneTileType::ROAD:
                    p.type = CarcassonnePawnType::THIEF;
                    std::cout << " a road";
                    break;
                case CarcassonneTileType::FIELD:
                    p.type = CarcassonnePawnType::PEASANT;
                    std::cout << " a field";
                    break;
                case CarcassonneTileType::MONASTERY:
                    p.type = CarcassonnePawnType::MONK;
                    std::cout << " a monastery";
                    break;
            }
            std::cout << std::endl;
            pawns.push_back(std::make_pair(p, tg));
            std::cout << "Pawn placed" << std::endl;
            std::cout << std::to_string(pawns.size()) << std::endl;
            switch (p.type) {
                case CarcassonnePawnType::KNIGHT:
                    std::cout << "Knight" << std::endl;
                    break;
                case CarcassonnePawnType::MONK:
                    std::cout << "Monk" << std::endl;
                    break;
                case CarcassonnePawnType::PEASANT:
                    std::cout << "Peasant" << std::endl;
                    break;
                case CarcassonnePawnType::THIEF:
                    std::cout << "Thief" << std::endl;
                    break;
            }
        }
        bool hasMonastery() const { return grid.at(CarcassonneTileGrid::CENTER_CENTER) == CarcassonneTileType::MONASTERY; }
        // get grid
        std::vector<std::pair<CarcassonnePawn, CarcassonneTileGrid>> getPawns() const { return pawns; }
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
        bool closedCity(const CarcassonneTile&, const std::pair<int,int>&);
        int closedCityRec(std::vector<std::pair<int,int>> ,  const CarcassonneTile& , const std::pair<int, int>& );
        bool anyMonastery(const CarcassonneTile&, const std::pair<int, int>& position);
        bool closedMonastery(const CarcassonneTile& ,const std::pair<int, int>& );
        bool finishedRoad(const CarcassonneTile& ,const std::pair<int, int>& );
};

/**
 * @brief A user interface for the Dominos game.
 * 
 */
class CarcassonneInterface : virtual public UserInterface<CarcassonneBoard, CarcassonneTile> {
    protected:
        sf::Texture tileSet;
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
    protected:
        std::vector<CarcassonneTile*> tiles;
        bool isPlacingPawn = false;
        std::map<std::string, CarcassonnePawnColor> playerColors;
        int currentTileX, currentTileY;
    public:
        Carcassonne(UserInterfaceProperties, BoardProperties);
        void drawGameScreen();
        void drawGameOverScreen();
        void handleEvent(const sf::Event&, sf::RenderWindow*);
        void handlePawnPlacement(sf::RenderWindow*);
        void registerPlayer(const std::string& name, CarcassonnePawnColor color) {
            scoreboard[scoreboard.size()] = std::make_pair(name, 0);
            playerColors[name] = color;
        }
};