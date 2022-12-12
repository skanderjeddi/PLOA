#include "../include/common.hpp"

/**
 * @brief Prints the tiles to the terminal
 * Since the tiles can be aligned in the terminal (when they're on the same y axis);
 * and since a tile's representation spans multiple lines, this function prints the tiles
 * to the terminal in a way that they're aligned.
 * 
 * @param ySort  A map of tiles sorted by y axis.
 * @param infs     The minimum x and y coordinates of the tiles.
 * @param sups   The maximum x and y coordinates of the tiles.
 * @param yk     The y coordinate of the tiles to print and the kth line to print.
 * @return std::string      The string to print.
 */
std::string tilesToString(std::map<int, std::map<int, Tile>> ySort, std::pair<int, int> infs, std::pair<int, int> sups, std::pair<int, int> yk) {
    auto line = std::string();
    auto y = yk.first;
    auto linesWithY = ySort[y];
    for (int x = 0; x <= sups.first - infs.first; x++) {
        if (linesWithY.find(x) != linesWithY.end()) { // If the tile is in the map.
            line += linesWithY[x].toLine(yk.second) + "\t"; // Appends kth line of the tile.
        } else {
            line += "        "; // Appends 8 spaces.
        }
    }
    return line;
}

/**
 * @brief Get a random integer between min and max.
 * 
 * @param min   The minimum value.
 * @param max   The maximum value.
 * @return int  The random integer.
 */
int randomInt(int min, int max) {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

/**
 * @brief Get a random float between 0 and 1.
 * 
 * @return float    The random float.
 */
float randomFloat() {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(rng);
}

/**
 * @brief Get the opposite side of a side.
 * 
 * @param side  The side.
 * @return Edge     The opposite side.
 */
Edge getOppositeSide(const Edge& side) {
    switch (side) {
        case Edge::TOP:
            return Edge::BOTTOM;
        case Edge::RIGHT:
            return Edge::LEFT;
        case Edge::BOTTOM:
            return Edge::TOP;
        case Edge::LEFT:
            return Edge::RIGHT;
        default:
            return Edge::TOP;
    }
}

/**
 * @brief Print a side to the terminal.
 * 
 * @param stream    The stream to print to.
 * @param side    The side to print.
 * @return std::ostream&    The stream.
 */
std::ostream& operator<<(std::ostream& stream, const Edge& side) {
    switch (side) {
        case Edge::TOP:
            stream << "TOP";
            break;
        case Edge::RIGHT:
            stream << "RIGHT";
            break;
        case Edge::BOTTOM:
            stream << "BOTTOM";
            break;
        case Edge::LEFT:
            stream << "LEFT";
            break;
    }
    return stream;
}