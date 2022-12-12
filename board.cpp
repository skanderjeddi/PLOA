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

/**
 * Generate a random tile that is guaranteed to fit on the board next to already placed tiles
 */
Tile Board::find_good_tile() {
    Tile good_tile;
    if (tiles.size() == 1) {
        if (random_in_0_1_range() > 0.5) {
            good_tile.values[TOP] = std::vector<int>(tiles.at(std::make_pair(0, 0)).values[BOTTOM]);
        } else {
            good_tile.values[LEFT] = std::vector<int>(tiles.at(std::make_pair(0, 0)).values[RIGHT]);
        }
        return good_tile;
    }
    for (auto tile : tiles) {
        auto coords = tile.first;
        auto neighbors = this->get_neighbours(coords.first, coords.second);
        if (neighbors.size() == 1) {
            switch (neighbors[0].first) {
                case TOP:
                    good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                    break;
                case RIGHT:
                    good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                    break;
                case BOTTOM:
                    good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                    break;
                case LEFT:
                    good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                    break;
            }
        } else if (neighbors.size() == 2) {
            auto n1 = neighbors[0];
            auto n2 = neighbors[1];
            switch (n1.first) {
                case TOP:
                    switch (n2.first) {
                        case TOP:
                            break;
                        case BOTTOM:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                            else
                                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                            break;
                        case LEFT:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                            else
                                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                            break;
                        case RIGHT:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                            else
                                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                            break;
                    }
                    break;
                case BOTTOM:
                    switch (n2.first) {
                        case BOTTOM:
                            break;
                        case TOP:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                            else
                                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                            break;
                        case LEFT:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                            else
                                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                            break;
                        case RIGHT:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                            else
                                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                            break;
                    }
                    break;
                case LEFT:
                    switch (n2.first) {
                        case BOTTOM:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                            else
                                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                            break;
                        case TOP:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
                            else
                                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                            break;
                        case LEFT:
                            break;
                        case RIGHT:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                            else
                                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                            break;
                    }
                    break;
                case RIGHT:
                    switch (n2.first) {
                        case BOTTOM:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                            else
                                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                            break;
                        case TOP:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
                            else
                                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                            break;
                        case LEFT:
                            if (random_in_0_1_range() > 0.5)
                                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
                            else
                                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
                            break;
                        case RIGHT:
                            break;
                    }
                    break;
            }
        } else if (neighbors.size() == 3) {
            auto n1 = neighbors[0];
            auto n2 = neighbors[1];
            auto n3 = neighbors[2];
            if (n1.first == TOP && n2.first == RIGHT && n3.first == BOTTOM) {
                good_tile.values[LEFT] = std::vector<int>(tile.second.values[RIGHT]);
            } else if (n1.first == TOP && n2.first == BOTTOM && n3.first == LEFT) {
                good_tile.values[RIGHT] = std::vector<int>(tile.second.values[LEFT]);
            } else if (n1.first == RIGHT && n2.first == BOTTOM && n3.first == LEFT) {
                good_tile.values[TOP] = std::vector<int>(tile.second.values[BOTTOM]);
            } else if (n1.first == TOP && n2.first == RIGHT && n3.first == LEFT) {
                good_tile.values[BOTTOM] = std::vector<int>(tile.second.values[TOP]);
            }
        } else {
            continue;
        }
    }
    return good_tile;
}

bool Board::can_place_tile(Tile candidate, int x, int y) {
    auto xy = std::make_pair(x, y);
    if (this->tiles.find(xy) != this->tiles.end()) {
        return false;
    }
    auto neighbours = this->get_neighbours(x, y);
    if (neighbours.size() == 0) { 
        return false;
    }
    for (auto neighbour : neighbours) {
        auto side = neighbour.first;
        auto tile = neighbour.second;
        for (int valueIndex = 0; valueIndex < 3; valueIndex++) {
            switch (side) {
                case TOP:
                    if (candidate.values[TOP][valueIndex] != tile.values[BOTTOM][valueIndex]) return false;
                    break;
                case RIGHT:
                    if (candidate.values[RIGHT][valueIndex] != tile.values[LEFT][valueIndex]) return false;
                    break;
                case BOTTOM:
                    if (candidate.values[BOTTOM][valueIndex] != tile.values[TOP][valueIndex]) return false;
                    break;
                case LEFT:
                    if (candidate.values[LEFT][valueIndex] != tile.values[RIGHT][valueIndex]) return false;
                    break;
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