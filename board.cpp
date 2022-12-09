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

std::ostream& operator<<(std::ostream& os, const Board& b) {
    // Sort the tiles into groups of same y
    auto tiles = std::map<int, std::vector<std::pair<int, Tile>>>();
    for (auto const& tile : b.tiles) {
        auto coord = tile.first;
        auto x = coord.first;
        auto y = coord.second;
        if (tiles.find(y) == tiles.end()) {
            tiles[y] = std::vector<std::pair<int, Tile>>();
        }
        tiles[y].push_back(std::make_pair(x, tile.second));
    }
    for (auto const& tile : tiles) {
        std::string line = "";
        auto tiles = tile.second;
        std::string spacing = "";
        for (int i = 0; i < 5; i++) {
            for (auto const& t : tiles) {
                int diff = 0;
                while (diff < t.first) {
                    spacing += "\t";
                    diff++;
                }
                line += t.second.line_repr(i) + spacing + "\t";
            }
            line += "\n";
            spacing = "";
        }
        os << line;
    }
    return os;
}