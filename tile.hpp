#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "common.hpp"

enum Side {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

enum Rotation {
    CLOCKWISE,
    COUNTERCLOCKWISE
};

class Tile {
private:
    std::map<Side, std::vector<int>> values;
    friend class Board;
    
public:
    Tile();
    Tile(std::map<Side, std::vector<int>> values) : values(values) {};
    Tile rotate(Rotation rotation);
    std::string line_representation(const int line) const;
    std::map<Side, std::vector<int>> get_values() const { return this->values; };
    friend std::ostream& operator<<(std::ostream& os, const Tile& tile);
    friend bool operator==(const Tile& tile1, const Tile& tile2);
}; 

#endif
