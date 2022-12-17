#pragma once

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"
#include "game.hpp"

#include "dominos.hpp"

class DominosTile : virtual public Tile<std::map<TileEdge, std::vector<int>>> {
    public:
        DominosTile();
        DominosTile(const std::map<TileEdge, std::vector<int>>&);
        DominosTile(const DominosTile&);
        void rotate(const TileRotation&);
};

class DominosBoard : virtual public Board<DominosTile> {
    public:
        DominosBoard(BoardProperties&);
        bool canSet(const DominosTile&, const std::pair<int, int>&) const;
};

class DominosInterface : virtual public UserInterface<DominosBoard, DominosTile> {
    public:
        DominosInterface(UserInterfaceProperties&, BoardProperties&);
        void draw(DominosBoard&);
        void drawBoard(DominosBoard&);
        void drawTile(DominosTile&, const sf::Vector2i&);
        void handleEvent(const sf::Event&);
};

class Dominos : virtual public Game<DominosTile, DominosBoard, DominosInterface> {
    public:
        Dominos(UserInterfaceProperties, BoardProperties);
        void run();
};