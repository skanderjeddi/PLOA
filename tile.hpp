#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "common.hpp"

#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3

class Tile {
private:
    std::vector<std::vector<int>> values;
    friend class Board;

public:
    Tile();
    Tile(std::vector<std::vector<int>> values) : values(values) {};
    void rotate();
    std::string line_repr(const int line) const;
    std::vector<std::vector<int>> get_values() const { return this->values; };
    friend std::ostream& operator<<(std::ostream& os, const Tile& t);
    friend bool operator==(const Tile& t1, const Tile& t2);
}; 

#endif
