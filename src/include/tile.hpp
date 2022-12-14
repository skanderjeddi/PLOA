#pragma once

#include "proto/tile.hpp"
#include "proto/common.hpp"

enum class Side {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

enum class Rotation {
    CLOCKWISE,
    COUNTERCLOCKWISE
};

class Tile {
    private:
        std::map<Side, std::vector<int>> sides;
        friend class Board;
    
    public:
        Tile();
        Tile(std::map<Side, std::vector<int>>& values) : sides(values) {};
        Tile(const Tile& tile) : sides(tile.sides) {};
        Tile rotate(const Rotation&) const;
        std::vector<int> getSide(const Side& edge) const { return this->sides.at(edge); };
        void setSide(const Side& edge, const std::vector<int>& values) { this->sides[edge] = values; };
        friend std::ostream& operator<<(std::ostream& stream, const Tile& tile);
        friend bool operator==(const Tile& tile1, const Tile& tile2);
};
std::vector<Tile> generateTiles(int);
