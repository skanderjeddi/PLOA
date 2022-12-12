#include "include/common.hpp"

using namespace std;

/**
 * @brief Construct a new Board object.
 * This constructor creates a new board with the initial tile placed in at (x, y).
 * 
 * @param initialTile           The initial tile to place on the board.
 * @param initialTilePosition   The position of the initial tile.
 * @return Board                The new board.
 */
Board::Board(Tile initialTile, pair<int, int> initialTilePosition) {
    this->tilesMap[initialTilePosition] = initialTile;
}

/**
 * @brief Generate random tiles.
 * This function generates a vector of random tiles.
 * Each tile is influenced by a previously randomly generated tile.
 * 
 * @param numberOfTiles       The number of tiles to generate.
 * @return std::vector<Tile>    The vector of random tiles.
 */
vector<Tile> Board::generateRandomTiles(int numberOfTiles) {
    // Preallocate the vector of tiles.
    auto randomTiles = vector<Tile>(numberOfTiles);
    for (int tileIndex = 0; tileIndex < numberOfTiles; tileIndex++) {
        // Generate a random tile at index i.
        randomTiles[tileIndex] = Tile();
        // Get a random side of the tile and compute its opposite.
        auto side = (Edge) randomInt(0, E - 1);
        auto oppositeSide = getOppositeSide(side);
        if (tileIndex == 0) { // If this is the first tile, set one of the edges to the same values of one of the initial tile's edges.
            auto initialTile = this->getInitialTile();
            randomTiles[tileIndex].getValues().at(side) = initialTile.getValues().at(oppositeSide);
        } else { // If this is not the first tile, set one of the edges to the same values of one of the previous tile's edges.
            auto randomIndex = randomInt(0, tileIndex - 1);
            randomTiles[tileIndex].getValues().at(side) = randomTiles[randomIndex].getValues().at(oppositeSide);
        }
    }
    return randomTiles;
} 

/**
 * @brief Get the neighboringEdges of a tile.
 * This function returns a vector of pairs of sides and tiles.
 * Each pair represents a neighboring tile and the side of the current tile that is adjacent to it.
 * 
 * @param x     The x coordinate of the tile.
 * @param y     The y coordinate of the tile.
 * @return std::vector<std::pair<Edge, Tile>>   The vector of pairs of sides and tiles.
 */
vector<pair<Edge, Tile>> Board::getNeighbors(int x, int y) const {
    vector<pair<Edge, Tile>> neighboringEdges;
    // Generate a vector of adjacent positions.
    auto adjacentPositions = vector<pair<int, int>> { 
        make_pair(x, y - 1),
        make_pair(x + 1, y),
        make_pair(x, y + 1),
        make_pair(x - 1, y)
    };
    for (int e = 0; e < E; e++) {
        auto neighbor = adjacentPositions[e];
        auto edge = (Edge) e;
        if (this->tilesMap.find(neighbor) != this->tilesMap.end()) {
            // If the neighbor exists, add it to the vector of neighboringEdges.
            auto tile = this->tilesMap.at(neighbor);
            neighboringEdges.push_back(std::make_pair(edge, tile));
        }
    }
    return neighboringEdges;
}

/**
 * @brief Check if a tile can be placed on the board.
 * This function checks if a tile can be placed on the board.
 * It checks if the tile is already placed on the board, and if it has any neighboringEdges.
 * If it has neighboringEdges, it checks if the values of the edges of the tile match the values of the edges of the neighboringEdges.
 * 
 * @param candidateTile     The tile to check.
 * @param x     The x coordinate of the tile.
 * @param y     The y coordinate of the tile.
 * @return true     If the tile can be placed on the board.
 * @return false    If the tile cannot be placed on the board.
 */
bool Board::canPlaceTile(Tile candidateTile, int x, int y) const {
    auto candidateCoords = make_pair(x, y);
    if (this->tilesMap.find(candidateCoords) != this->tilesMap.end()) {
        return false; // The tile is already placed on the board.
    }
    auto neighboringEdges = this->getNeighbors(x, y);
    if (neighboringEdges.size() == 0) {
        return false; // The tile must have at least one neighbor.
    }
    for (auto neighbor : neighboringEdges) { // Check if the values of the edges of the tile match the values of the edges of the neighboringEdges.
        auto neighborSide = neighbor.first;
        auto neighborTile = neighbor.second;
        auto oppositeSide = getOppositeSide(neighborSide);
        if (candidateTile.getValues().at(neighborSide) != neighborTile.getValues().at(oppositeSide)) {
            return false; // The values of the edges of the tile do not match the values of the edges of the neighboringEdges.
        }
    }
    return true; // The tile can be placed on the board.
}

/**
 * @brief Place a tile on the board.
 * This function places a tile on the board.
 * 
 * @param newTile  The tile to place.
 * @param x     The x coordinate of the tile.
 * @param y     The y coordinate of the tile.
 */
void Board::placeTile(Tile newTile, int x, int y) {
    this->tilesMap[make_pair(x, y)] = newTile;
}

/**
 * @brief Get a tile from its coordinates.
 * 
 * @param x     The x coordinate of the tile.
 * @param y     The y coordinate of the tile.
 * @return Tile     The tile at the given coordinates.
 */
Tile Board::retrieveTile(int x, int y) const {
    return this->tilesMap.at(make_pair(x, y));
}

/**
 * @brief Find a free neighboring side to a tile through its neighboringEdges' list.
 * It picks a random side that is not already occupied by a neighbor.
 * 
 * @param neighboringEdges     The list of neighboringEdges of the tile.
 * @return Side     The side that is free.
 */
Edge Board::findFreeEdge(vector<Edge> neighboringEdges) const {
    vector<Edge> possibleTargets;
    if (neighboringEdges.size() == 0) { // If the tile has no neighboringEdges, all sides are possible.
        for (int e = 0; e < E; e++) {
            possibleTargets.push_back((Edge) e);
        }
    } else if (neighboringEdges.size() == 1) { // If the tile has one neighbor, all sides except the one that is already occupied are possible.
        for (int e = 0; e < E; e++) {
            if ((Edge) e != neighboringEdges[0]) {
                possibleTargets.push_back((Edge) e);
            }
        }
    } else if (neighboringEdges.size() == 2) { // If the tile has two neighboringEdges, all sides except the two that are already occupied are possible.
        for (int e = 0; e < E; e++) {
            if ((Edge) e != neighboringEdges[0] && (Edge) e != neighboringEdges[1]) {
                possibleTargets.push_back((Edge) e);
            }
        }
    } else if (neighboringEdges.size() == 3) { // If the tile has three neighboringEdges, all sides except the three that are already occupied are possible.
        for (int e = 0; e < E; e++) {
            if ((Edge) e != neighboringEdges[0] && (Edge) e != neighboringEdges[1] && (Edge) e != neighboringEdges[2]) {
                possibleTargets.push_back((Edge) e);
            }
        }
    }
    // Pick a random side from the possible targets.
    return possibleTargets[randomInt(0, possibleTargets.size() - 1)];
}

/**
 * @brief Find a tile that fits somewhere on the board.
 * 
 * @return Tile     The tile that fits somewhere on the board.
 */
Tile Board::findTileThatFits() const {
    Tile fittingTile;
    for (auto currentTile : tilesMap) { // For each tile on the board.
        auto coords = currentTile.first;
        auto neighboringEdges = this->getNeighbors(coords.first, coords.second);
        if (neighboringEdges.size() == 4) { // If a tile has 4 neighboringEdges, no tile can be placed next to it.
            continue;
        }
        auto neighborsSides = std::vector<Edge>();
        for (auto neighbor : neighboringEdges) {
            neighborsSides.push_back(neighbor.first);
        } // Get the sides of the neighboringEdges.
        auto targetSide = findFreeEdge(neighborsSides); // Find a free side.
        auto oppositeSide = getOppositeSide(targetSide);
        // Create a new tile with the values of the current tile, but with the values of the target side replaced by the values of the opposite side.
        fittingTile.valuesByEdge[targetSide] = currentTile.second.valuesByEdge[oppositeSide];
    }
    return fittingTile;
}

/**
 * @brief Get the board's initial tile.
 * 
 * @return Tile     The board's initial tile.
 */
Tile Board::getInitialTile() const {
    return this->tilesMap.at(make_pair(0, 0));
}

/**
 * @brief Print the board.
 * 
 * @param stream    The stream to print to.
 * @param board     The board to print.
 * @return std::ostream&    The stream.
 */
ostream& operator<<(ostream& stream, const Board& board) {
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
    auto translatedTiles = map<pair<int, int>, Tile>();
    for (auto const& currentTile : board.tilesMap) {
        auto coords = currentTile.first;
        auto x = coords.first;
        auto y = coords.second;
        translatedTiles[make_pair(x - minX, y - minY)] = currentTile.second; // Translate the x and y of the tile to be centered at 0
    }
    // Sort newTiles by y keeping x somewhere
    auto sortedByYTiles = map<int, map<int, Tile>>();
    for (auto const& translateTile : translatedTiles) {
        auto coords = translateTile.first;
        auto x = coords.first;
        auto y = coords.second;
        if (sortedByYTiles.find(y) == sortedByYTiles.end()) {
            sortedByYTiles[y] = map<int, Tile>(); // If the y is not in the map, add it.
        }
        sortedByYTiles[y][x] = translateTile.second; // Add the tile to the map.
    }
    for (int y = 0; y <= maxY - minY; y++) {
        for (int k = 0; k < 5; k++) {
            // Print the tiles to the terminal with the x and y centered at 0.
            stream << tilesToString(sortedByYTiles, make_pair(minX, minY), make_pair(maxX, maxY), make_pair(y, k)) << endl;
        }
    }
    return stream;
}