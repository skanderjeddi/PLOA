#include "common.hpp"

Board::Board(Tile initial) {
    this->tiles[std::make_pair(0, 0)] = initial;
}

std::vector<std::pair<Side, Tile>> Board::get_neighbours(int x, int y) {
    std::vector<std::pair<Side, Tile>> adjacent;
    auto neighbours = std::vector<std::pair<int, int>> { 
        std::make_pair(x, y - 1),
        std::make_pair(x + 1, y),
        std::make_pair(x, y + 1),
        std::make_pair(x - 1, y)
    };
    for (int i = 0; i < 4; i++) {
        auto neighbour = neighbours[i];
        if (this->tiles.find(neighbour) != this->tiles.end()) {
            adjacent.push_back(std::make_pair((Side) i, this->tiles[neighbour]));
        }
    }
    return adjacent;
}

bool Board::can_place_tile(Tile tile, int x, int y) {
    auto xy = std::make_pair(x, y);
    if (this->tiles.find(xy) != this->tiles.end()) {
        return false;
    }
    auto neighbours = this->get_neighbours(x, y);
    for (auto neighbour : neighbours) {
        auto side = neighbour.first;
        auto tile = neighbour.second;
        for (int valueIndex = 0; valueIndex < 3; valueIndex++) {
            switch (side) {
                case TOP:
                    if (tile.values[TOP][valueIndex] != tile.values[BOTTOM][valueIndex]) return false;
                case RIGHT:
                    if (tile.values[RIGHT][valueIndex] != tile.values[LEFT][valueIndex]) return false;
                case BOTTOM:
                    if (tile.values[BOTTOM][valueIndex] != tile.values[TOP][valueIndex]) return false;
                case LEFT:
                    if (tile.values[LEFT][valueIndex] != tile.values[RIGHT][valueIndex]) return false;
            }
        }
    }
    return true;
}

void Board::place_tile(Tile tile, int x, int y) {
    this->tiles[std::make_pair(x, y)] = tile;
}

std::ostream& operator<<(std::ostream& os, const Board& board) {
    // Find the min and max x and y of board.tiles and put them in 2 std::pairs
    auto min_x = 0; auto max_x = 0;
    auto min_y = 0; auto max_y = 0; 
    for (auto const& tile : board.tiles) {
        auto coord = tile.first;
        auto x = coord.first;
        auto y = coord.second;
        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }
    // Create new tiles map with the x and y centered at 0
    auto new_tiles = std::map<std::pair<int, int>, Tile>();
    for (auto const& tile : board.tiles) {
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
            os << tiles_to_terminal(tiles, std::make_pair(min_x, min_y), std::make_pair(max_x, max_y), y, k) << std::endl;
        }
    }
    return os;
}