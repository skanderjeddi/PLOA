#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "common.hpp"

class Board {
private:
    std::map<std::pair<int, int>, Tile> tiles;
    friend class Tile;

public:
    Board(Tile initial);
    bool can_place_tile(Tile new_tile, int x, int y);
    void place_tile(Tile new_tile, int x, int y);
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
};

#endif