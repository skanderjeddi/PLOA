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
            auto tile = this->tiles[coord];
            switch (i) {
                case RIGHT: // NEW TILE IS TO THE LEFT
                    if (new_tile.values[RIGHT][0] != tile.values[LEFT][0] ||
                        new_tile.values[RIGHT][1] != tile.values[LEFT][1] ||
                        new_tile.values[RIGHT][2] != tile.values[LEFT][2]) {
                            can_place = false;
                        }
                    break;
                case TOP: 
                    if (new_tile.values[TOP][0] != tile.values[BOTTOM][0] ||
                        new_tile.values[TOP][1] != tile.values[BOTTOM][1] ||
                        new_tile.values[TOP][2] != tile.values[BOTTOM][2]) {
                            can_place = false;
                        }
                    break;
                case BOTTOM: // NEW TILE IS TO THE TOP
                    if (new_tile.values[BOTTOM][0] != tile.values[TOP][0] ||
                        new_tile.values[BOTTOM][1] != tile.values[TOP][1] ||
                        new_tile.values[BOTTOM][2] != tile.values[TOP][2]) {
                            can_place = false;
                        }
                    break;
                case LEFT: // NEW TILE IS TO THE RIGHT
                    if (new_tile.values[LEFT][0] != tile.values[RIGHT][0] ||
                        new_tile.values[LEFT][1] != tile.values[RIGHT][1] ||
                        new_tile.values[LEFT][2] != tile.values[RIGHT][2]) {
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
    // Find the minimum x and y coordinates
    auto xcoords = std::vector<int>();
    auto ycoords = std::vector<int>();
    for (auto const& mapping : b.tiles) {
        xcoords.push_back(mapping.first.first);
        ycoords.push_back(mapping.first.second);
    }
    auto minx = *std::min_element(xcoords.begin(), xcoords.end());
    auto miny = *std::min_element(ycoords.begin(), ycoords.end());
    // Copy the tiles into a new map with the minimum coordinates at 0, 0
    auto newtiles = std::map<std::pair<int, int>, Tile>();
    for (auto const& mapping : b.tiles) {
        auto newx = mapping.first.first - minx;
        auto newy = mapping.first.second - miny;
        newtiles[std::make_pair(newx, newy)] = mapping.second;
    }
    auto old_tiles = std::vector<Tile>();
    for (const auto &mapping : b.tiles) {
        old_tiles.push_back(mapping.second);
    }
    // Print the tiles
    for (size_t x = 0; x < newtiles.size(); x++) {
        auto current_tiles = std::vector<Tile>();
        std::string big_line = "";
        for (size_t y = 0; y < newtiles.size(); y++) {
            auto coord = std::make_pair(x, y);
            if (newtiles.find(coord) != newtiles.end()) {
                current_tiles.push_back(newtiles[coord]);
            } else {
                current_tiles.push_back(Tile());
            }
        }
        for (int side = 0; side < 5; side++) {
            for (size_t i = 0; i < current_tiles.size(); i++) {
                if (std::find(old_tiles.begin(), old_tiles.end(), current_tiles[i]) != old_tiles.end())
                    big_line += current_tiles[i].line_repr(side) + "\t";
                else 
                    big_line += "\t";
            }
            big_line += "\n";
        }
        os << big_line;
    }
    return os;
}