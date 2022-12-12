#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "common.hpp"

#define EDGES 4
#define VALUES 3

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
        std::map<Side, std::vector<int>> valuesByEdge;
        friend class Board;
    
public:
    Tile();
    Tile(std::map<Side, std::vector<int>> values) : valuesByEdge(values) {};
    Tile rotate(const Rotation rotation) const;
    std::string toLine(const int line) const;
    std::map<Side, std::vector<int>> getValues() const { return this->valuesByEdge; };
    friend std::ostream& operator<<(std::ostream& stream, const Tile& tile);
    friend bool operator==(const Tile& tile1, const Tile& tile2);
};

#endif
