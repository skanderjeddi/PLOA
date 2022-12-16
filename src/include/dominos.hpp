#pragma once

#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"

#include "dominos.hpp"

class DominosTile : virtual public Tile<std::map<TileEdge, std::vector<int>>> {
    public:
        DominosTile();
        DominosTile(const std::map<TileEdge, std::vector<int>>&);
        DominosTile(const DominosTile&);
        void rotate(const TileRotation&);
        void draw(sf::RenderWindow&, const sf::Vector2i&, const sf::Vector2i&);
};

class DominosBoard : virtual public Board<DominosTile> {
    public:
        DominosBoard(int, int);
        DominosBoard(const DominosBoard&);
        void draw(sf::RenderWindow&, const sf::Vector2i&);
};