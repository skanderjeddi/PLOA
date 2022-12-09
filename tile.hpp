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
    bool is_blank;
    friend class Board;

public:
    Tile();
    std::string line_repr(const int line) const;
    friend std::ostream& operator<<(std::ostream& os, const Tile& t);
    friend bool operator==(const Tile& t1, const Tile& t2);
}; 

#endif
