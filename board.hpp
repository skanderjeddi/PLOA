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
    std::string print_line(std::map<int, std::map<int, Tile>> sorted_tiles, std::pair<int, int>, std::pair<int, int>, int y, int k) const;
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
};

#endif