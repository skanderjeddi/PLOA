#include "include/common.hpp"

Board::Board(Tile initialTile) {
    this->tilesMap[std::make_pair(0, 0)] = initialTile;
}

std::vector<Tile> Board::generateRandomTiles(int number_of_tiles) {
    auto randomTiles = std::vector<Tile>(number_of_tiles);
    for (int i = 0; i < number_of_tiles; i++) {
        randomTiles[i] = Tile();
        if (i == 0) {
            auto side = (Side) randomInRange(0, EDGES - 1);
            auto initialTile = this->getInitialTile();
            randomTiles[i].getValues().at(side) = initialTile.getValues().at(this->getOppositeSide(side));
        } else {
            auto side = (Side) randomInRange(0, EDGES - 1);
            auto randomIndex = randomInRange(0, i - 1);
            randomTiles[i].getValues().at(side) = randomTiles[randomIndex].getValues().at(this->getOppositeSide(side));
        }
    }
    return randomTiles;
} 

std::vector<std::pair<Side, Tile>> Board::getNeighbors(int x, int y) const {
    std::vector<std::pair<Side, Tile>> neighbors;
    auto adjacentPositions = std::vector<std::pair<int, int>> { 
        std::make_pair(x, y - 1),
        std::make_pair(x + 1, y),
        std::make_pair(x, y + 1),
        std::make_pair(x - 1, y)
    };
    for (int i = 0; i < EDGES; i++) {
        auto neighbor = adjacentPositions[i];
        if (this->tilesMap.find(neighbor) != this->tilesMap.end()) {
            neighbors.push_back(std::make_pair((Side) i, this->tilesMap.at(neighbor)));
        }
    }
    return neighbors;
}

bool Board::canPlaceTile(Tile candidateTile, int x, int y) const {
    auto coords = std::make_pair(x, y);
    if (this->tilesMap.find(coords) != this->tilesMap.end()) {
        return false;
    }
    auto neighbors = this->getNeighbors(x, y);
    if (neighbors.size() == 0) { 
        return false;
    }
    for (auto neighbor : neighbors) {
        auto neighborSide = neighbor.first;
        auto neighborTile = neighbor.second;
        for (int k = 0; k < VALUES; k++) {
            if (candidateTile.valuesByEdge[neighborSide][k] != neighborTile.valuesByEdge[getOppositeSide(neighborSide)][k]) {
                return false;
            }
        }
    }
    return true;
}

void Board::placeTile(Tile newTile, int x, int y) {
    this->tilesMap[std::make_pair(x, y)] = newTile;
}

Tile Board::retrieveTile(int x, int y) const {
    return this->tilesMap.at(std::make_pair(x, y));
}

Side Board::getOppositeSide(Side side) const {
    switch (side) {
        case Side::TOP:
            return Side::BOTTOM;
        case Side::RIGHT:
            return Side::LEFT;
        case Side::BOTTOM:
            return Side::TOP;
        case Side::LEFT:
            return Side::RIGHT;
        default:
            return Side::TOP;
    }
}

Side Board::findFreeNeighboringSide(std::vector<Side> neighbors) const {
    std::vector<Side> possibleTargets;
    if (neighbors.size() == 0) {
        for (int i = 0; i < EDGES; i++) {
            possibleTargets.push_back((Side) i);
        }
    } else if (neighbors.size() == 1) {
        for (int i = 0; i < EDGES; i++) {
            if ((Side) i != neighbors[0]) {
                possibleTargets.push_back((Side) i);
            }
        }
    } else if (neighbors.size() == 2) {
        for (int i = 0; i < EDGES; i++) {
            if ((Side) i != neighbors[0] && (Side) i != neighbors[1]) {
                possibleTargets.push_back((Side) i);
            }
        }
    } else if (neighbors.size() == 3) {
        for (int i = 0; i < EDGES; i++) {
            if ((Side) i != neighbors[0] && (Side) i != neighbors[1] && (Side) i != neighbors[2]) {
                possibleTargets.push_back((Side) i);
            }
        }
    }
    return possibleTargets[randomInRange(0, possibleTargets.size() - 1)];
}

Tile Board::findAppropriateTile() const {
    Tile appropriateTile;
    for (auto currentTile : tilesMap) {
        auto coords = currentTile.first;
        auto neighbors = this->getNeighbors(coords.first, coords.second);
        if (neighbors.size() == 4) {
            continue;
        }
        auto neighborsSides = std::vector<Side>();
        for (auto neighbor : neighbors) {
            neighborsSides.push_back(neighbor.first);
        }
        auto target_side = findFreeNeighboringSide(neighborsSides);
        appropriateTile.valuesByEdge[target_side] = currentTile.second.valuesByEdge[getOppositeSide(target_side)];
    }
    return appropriateTile;
}

Tile Board::getInitialTile() const {
    return this->tilesMap.at(std::make_pair(0, 0));
}

std::ostream& operator<<(std::ostream& stream, const Board& board) {
    // Find the min and max x and y of board.tiles and put them in 2 pairs
    auto minX = 0; auto maxX = 0;
    auto minY = 0; auto maxY = 0; 
    for (auto const& currentTile : board.tilesMap) {
        auto currentCoords = currentTile.first;
        auto x = currentCoords.first;
        auto y = currentCoords.second;
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }
    // Create new tiles map with the x and y centered at 0
    auto translatedTiles = std::map<std::pair<int, int>, Tile>();
    for (auto const& currentTile : board.tilesMap) {
        auto coords = currentTile.first;
        auto x = coords.first;
        auto y = coords.second;
        translatedTiles[std::make_pair(x - minX, y - minY)] = currentTile.second;
    }
    // Sort new_tiles by y keeping x somewhere
    auto sortedByYTiles = std::map<int, std::map<int, Tile>>();
    for (auto const& translateTile : translatedTiles) {
        auto coords = translateTile.first;
        auto x = coords.first;
        auto y = coords.second;
        if (sortedByYTiles.find(y) == sortedByYTiles.end()) {
            sortedByYTiles[y] = std::map<int, Tile>();
        }
        sortedByYTiles[y][x] = translateTile.second;
    }
    for (int y = 0; y <= maxY - minY; y++) {
        for (int k = 0; k < 5; k++) {
            stream << printTilesToTerminal(sortedByYTiles, std::make_pair(minX, minY), std::make_pair(maxX, maxY), y, k) << std::endl;
        }
    }
    return stream;
}