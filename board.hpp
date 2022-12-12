#ifndef __BOARD_HPP__
#define __BOARD_HPP__

class Board {
private:
    std::map<std::pair<int, int>, Tile> tiles;
    friend class Tile;

public:
    Board(Tile initial);
    std::vector<std::pair<Side, Tile>> get_neighbours(int x, int y);
    bool can_place_tile(Tile new_tile, int x, int y);
    void place_tile(Tile new_tile, int x, int y);
    Tile find_good_tile();
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
};

#endif