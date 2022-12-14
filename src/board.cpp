#include "include/common.hpp"
#include "include/tile.hpp"
#include "include/board.hpp"

Board::Board(int width, int height) : width(width), height(height) {
    this->tiles = std::map<std::pair<int, int>, Tile>();
    this->placeTile(Tile(), std::make_pair(width / 2, height / 2));
}

std::vector<std::pair<Side, Tile>> Board::gatherAdjacentTiles(const std::pair<int, int>& position) const {
    std::vector<std::pair<Side, Tile>> adjacentTiles;
    int x = position.first;
    int y = position.second;
    auto directions = std::vector<std::pair<int, int>> { 
        std::make_pair(x, y - 1),
        std::make_pair(x + 1, y),
        std::make_pair(x, y + 1),
        std::make_pair(x - 1, y)
    };
    for (int i = 0; i < 4; i++) {
        auto direction = directions[i];
        auto side = (Side) i;
        if (this->tiles.find(direction) != this->tiles.end()) {
            auto tile = this->tiles.at(direction);
            adjacentTiles.push_back(std::make_pair(side, tile));
        }
    }
    return adjacentTiles;
}

bool Board::canPlaceTile(const Tile& candidateTile, const std::pair<int, int>& position) const {
    if (this->tiles.find(position) != this->tiles.end()) {
        return false; // The tile is already placed on the board.
    }
    auto adjacentTiles = this->gatherAdjacentTiles(position);
    if (adjacentTiles.size() == 0) {
        return false; // The tile must have at least one neighbor.
    }
    for (auto adjacentTile : adjacentTiles) { // Check if the values of the edges of the tile match the values of the edges of the neighboringEdges.
        auto adjacentSide = adjacentTile.first;
        auto oppositeSide = getOppositeSide(adjacentSide);
        for (int i = 0; i < 3; i++) {
            if (candidateTile.getSide(adjacentSide)[i] != adjacentTile.second.getSide(oppositeSide)[i]) {
                return false; // The values of the edges of the tile do not match the values of the edges of the neighboringEdges.
            }
        }
    }
    return true; // The tile can be placed on the board.
}

void Board::placeTile(const Tile& newTile, const std::pair<int, int>& position) {
    this->tiles[position] = newTile;
}

Tile* Board::getTile(const std::pair<int, int>& position) {
    if (this->tiles.find(position) == this->tiles.end()) {
        return nullptr;
    }
    return &this->tiles.at(position);
}

Side Board::findFreeSide(const std::vector<Side>& adjacentSides) const {
    // Check if a certain side is in adjacentSides.
    auto allSides = std::vector<Side>{ Side::TOP, Side::RIGHT, Side::BOTTOM, Side::LEFT };
    std::vector<Side> possibleTargets;
    if (adjacentSides.size() == 0) { // If the tile has no neighboringEdges, all sides are possible.
        for (int i = 0; i < 4; i++) {
            possibleTargets.push_back((Side) i);
        }
    } else if (adjacentSides.size() == 1) { // If the tile has one neighbor, all sides except the one that is already occupied are possible.
        for (int i = 0; i < 4; i++) {
            if ((Side) i != adjacentSides[0]) {
                possibleTargets.push_back((Side) i);
            }
        }
    } else if (adjacentSides.size() == 2) { // If the tile has two neighboringEdges, all sides except the two that are already occupied are possible.
        for (int i = 0; i < 4; i++) {
            if ((Side) i != adjacentSides[0] && (Side) i != adjacentSides[1]) {
                possibleTargets.push_back((Side) i);
            }
        }
    } else if (adjacentSides.size() == 3) { // If the tile has three neighboringEdges, all sides except the three that are already occupied are possible.
        for (int i = 0; i < 4; i++) {
            if ((Side) i != adjacentSides[0] && (Side) i != adjacentSides[1] && (Side) i != adjacentSides[2]) {
                possibleTargets.push_back((Side) i);
            }
        }
    }
    return possibleTargets[randomInt(0, possibleTargets.size() - 1)];
}

Tile Board::fitNewTile() const {
    Tile fittingTile;
    bool found = false;
    while (!found) {
        int randomX = randomInt(0, width - 1);
        int randomY = randomInt(0, height - 1);
        auto position = std::make_pair(randomX, randomY);
        if (this->tiles.find(position) == this->tiles.end()) {
            continue;
        }
        auto adjacentTiles = this->gatherAdjacentTiles(position);
        if (adjacentTiles.size() == 0) {
            continue;
        }
        for (auto adjacentTile : adjacentTiles) {
            fittingTile.setSide(adjacentTile.first, adjacentTile.second.getSide(getOppositeSide(adjacentTile.first)));
        }
    }
    return fittingTile;
    /** for (auto currentTile : tiles) { // For each tile on the board.
        auto current_position = currentTile.first;
        auto adjacentTiles = this->gatherAdjacentTiles(current_position);
        if (adjacentTiles.size() == 4) { // If a tile has 4 neighboringEdges, no tile can be placed next to it.
            continue;
        } else {

        }
        auto adjacentSides = std::std::vector<Side>();
        for (auto adjacentSide : adjacentTiles) {
            adjacentSides.push_back(adjacentSide.first);
        } // Get the sides of the neighboringEdges.
        auto target = findFreeSide(adjacentSides); // Find a free side.
        auto oppositeSide = getOppositeSide(target);
        // Create a new tile with the values of the current tile, but with the values of the target side replaced by the values of the getOppositeSide side.
        fittingTile.sides[oppositeSide] = std::std::vector<int>(currentTile.second.sides[target]);
    }
    return fittingTile; **/
}