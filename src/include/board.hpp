#pragma once

#include "proto/board.hpp"
#include "proto/tile.hpp"
#include "proto/common.hpp"

class Board {
    private:
        int width, height;
        std::map<std::pair<int, int>, Tile> tiles;
        friend class Tile;
        friend class Dominos;
    public:
        Board(int, int);
        std::vector<std::pair<Side, Tile>> gatherAdjacentTiles(const std::pair<int, int>&) const;
        bool canPlaceTile(const Tile&, const std::pair<int, int>&) const;
        void placeTile(const Tile&, const std::pair<int, int>&);
        Side findFreeSide(const std::vector<Side>&) const; 
        Tile* getTile(const std::pair<int, int>&);
        Tile fitNewTile() const;
        int getWidth() const { return width; }
        int getHeight() const { return height; }
};
