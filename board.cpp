#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"

Board::Board(Tile initial) {
    this->tiles[std::make_pair(0, 0)] = initial;
}

bool Board::can_place_tile(Tile new_tile, int x, int y) {
    // Check if a tile is already placed
    if (this->tiles.find(std::make_pair(x, y)) != this->tiles.end()) {
        return false;
    }
    // Check if the tile can be placed
    auto adjacent = std::vector<std::pair<int, int>>();
    adjacent.push_back(std::make_pair(x + 1, y));
    adjacent.push_back(std::make_pair(x, y - 1));
    adjacent.push_back(std::make_pair(x, y + 1));
    adjacent.push_back(std::make_pair(x - 1, y));
    auto can_place = true;
    for (size_t i = 0; i < adjacent.size(); i++) {
        auto const& coord = adjacent[i];
        if (this->tiles.find(coord) != this->tiles.end()) {
            auto adj = this->tiles[coord];
            switch (i) {
                case RIGHT: // NEW TILE IS TO THE LEFT
                    if (new_tile.values[RIGHT][0] != adj.values[LEFT][0] ||
                        new_tile.values[RIGHT][1] != adj.values[LEFT][1] ||
                        new_tile.values[RIGHT][2] != adj.values[LEFT][2]) {
                            can_place = false;
                        }
                    break;
                case TOP: 
                    if (new_tile.values[TOP][0] != adj.values[BOTTOM][0] ||
                        new_tile.values[TOP][1] != adj.values[BOTTOM][1] ||
                        new_tile.values[TOP][2] != adj.values[BOTTOM][2]) {
                            can_place = false;
                        }
                    break;
                case BOTTOM: // NEW TILE IS TO THE TOP
                    if (new_tile.values[BOTTOM][0] != adj.values[TOP][0] ||
                        new_tile.values[BOTTOM][1] != adj.values[TOP][1] ||
                        new_tile.values[BOTTOM][2] != adj.values[TOP][2]) {
                            can_place = false;
                        }
                    break;
                case LEFT: // NEW TILE IS TO THE RIGHT
                    if (new_tile.values[LEFT][0] != adj.values[RIGHT][0] ||
                        new_tile.values[LEFT][1] != adj.values[RIGHT][1] ||
                        new_tile.values[LEFT][2] != adj.values[RIGHT][2]) {
                            can_place = false;
                        }
                    break;
            }
        }
    }
    return can_place;
}

void Board::place_tile(Tile new_tile, int x, int y) {
    this->tiles[std::make_pair(x, y)] = new_tile;
}

std::string Board::print_line(std::map<int, std::map<int, Tile>> sorted_tiles, std::pair<int, int> min_values, std::pair<int, int> max_values, int y, int k) const {
    std::string line = std::string();
    auto ys = sorted_tiles[y];
    for (int x = 0; x <= min_values.first + max_values.first; x++) {
        if (ys.find(x) != ys.end()) {
            line += ys[x].line_repr(k) + "\t";
        } else {
            line += "        ";
        }
    }
    return line;
}

std::ostream& operator<<(std::ostream& os, const Board& b) {
    // Find the min and max x and y of b.tiles and put them in 2 std::pairs
    auto min_x = 0; auto max_x = 0;
    auto min_y = 0; auto max_y = 0; 
    for (auto const& tile : b.tiles) {
        auto coord = tile.first;
        auto x = coord.first;
        auto y = coord.second;
        if (x < min_x) {
            min_x = x;
        }
        if (x > max_x) {
            max_x = x;
        }
        if (y < min_y) {
            min_y = y;
        }
        if (y > max_y) {
            max_y = y;
        }
    }
    // Create new tiles map with the x and y centered at 0
    auto new_tiles = std::map<std::pair<int, int>, Tile>();
    for (auto const& tile : b.tiles) {
        auto coord = tile.first;
        auto x = coord.first;
        auto y = coord.second;
        new_tiles[std::make_pair(x - min_x, y - min_y)] = tile.second;
    }
    // Sort new_tiles by y keeping x somewhere
    auto tiles = std::map<int, std::map<int, Tile>>();
    for (auto const& tile : new_tiles) {
        auto coord = tile.first;
        auto x = coord.first;
        auto y = coord.second;
        if (tiles.find(y) == tiles.end()) {
            tiles[y] = std::map<int, Tile>();
        }
        tiles[y][x] = tile.second;
    }
    for (int y = 0; y <= max_y + min_y; y++) {
        for (int k = 0; k < 5; k++) {
            os << b.print_line(tiles, std::make_pair(min_x, min_y), std::make_pair(max_x, max_y), y, k) << std::endl;
        }
    }
    return os;
}