#include "include/tile.hpp"
#include "include/common.hpp"

Tile::Tile() {
    this->sides = std::map<Side, std::vector<int>>();
    for (int i = 0; i < 4; i++) {
        auto side = (Side) i;
        this->sides[side] = std::vector<int>(3);
        for (int value = 0; value < 3; value++) {
            this->sides[side][value] = randomInt(1, 6);
        }
    }
}

Tile Tile::rotate(const Rotation& rotation) const {
    /** auto rotatedValues = map<Side, vector<int>>();
    auto backup = vector<int>(12); // create a backup of the values
    for (int i = 0; i < 4; i++) {
        auto side = (Side) i; // cast int to Edge enum
        auto sideValues = this->sides.at(side); // getTile the values of the current side
        for (int j = 0; j < 3; j++) {
            backup[i * 3 + j] = sideValues[j]; // backup the values using a 1D array
        }
    }
    if (rotation == Rotation::CLOCKWISE) { // rotate the values clockwise 
        int i = 0;
        for (Side s : { Side::RIGHT, Side::BOTTOM, Side::LEFT, Side::TOP }) {
            rotatedValues[s] = { backup[i], backup[i + 1], backup[i + 2] };
            i += 3;
        }
    } else { // rotate the values counterclockwise
        int i = 0;
        for (Side s : { Side::LEFT, Side::TOP, Side::RIGHT, Side::BOTTOM }) {
            rotatedValues[s] = { backup[i], backup[i + 1], backup[i + 2] };
            i += 3;
        }
    } **/
    auto rotatedValues = std::map<Side, std::vector<int>>();
    if (rotation == Rotation::CLOCKWISE) { // rotate the values clockwise 
        int i = 0;
        for (Side s : { Side::RIGHT, Side::BOTTOM, Side::LEFT, Side::TOP }) {
            rotatedValues[s] = this->sides.at((Side) i);
            i++;
        }
    } else { // rotate the values counterclockwise
        int i = 0;
        for (Side s : { Side::LEFT, Side::TOP, Side::RIGHT, Side::BOTTOM }) {
            rotatedValues[s] = this->sides.at((Side) i);
            i++;
        }
    }
    return Tile(rotatedValues);
}

std::vector<Tile> generateTiles(int n) {
    auto tiles = std::vector<Tile>(n);
    for (int i = 0; i < n; i++) {
        // Generate a random tile at index i.
        tiles[i] = Tile();
        // Get a random side of the tile and compute its getOppositeSide.
        auto randomSide = (Side) randomInt(0, 3);
        auto oppositeSide = getOppositeSide(randomSide);
        if (i == 0) { // If this is the first tile, set one of the edges to the same values of one of the initial tile's edges.
            continue;
        } else { // If this is not the first tile, set one of the edges to the same values of one of the previous tile's edges.
            auto j = randomInt(0, i - 1);
            tiles[i].getSide(randomSide) = tiles[j].getSide(oppositeSide);
        }
    }
    return tiles;
}

bool operator==(const Tile& tile1, const Tile& tile2) {
    for (int i = 0; i < 4; i++) {
        auto side = (Side) i;
        auto values1 = tile1.sides.at(side);
        auto values2 = tile2.sides.at(side);
        for (int j = 0; j < 3; j++) {
            if (values1[j] != values2[j]) {
                return false;
            }
        }
    }
    return true;
}

