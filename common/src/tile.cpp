#include "../include/common.hpp"

/**
 * @brief Construct a new Tile object
 * This constructor generates a random tile. It generates a random value for each edge of the tile.
 * The values are generated between 1 and 6.
 */
Tile::Tile() {
    this->valuesByEdge = std::map<Edge, std::vector<int>>();
    for (int i = 0; i < E; i++) {
        auto side = (Edge) i; // cast int to Edge enum
        this->valuesByEdge[side] = std::vector<int>(E);
        for (int value = 0; value < V; value++) {
            // generate a random int between 1 and 6
            auto randomValue = randomInt(1, 6);
            this->valuesByEdge[side][value] = randomValue;
        }
    }
}

/**
 * @brief Rotate a tile
 * This function rotates a tile clockwise or counterclockwise. It returns a new tile with the rotated values.
 * 
 * @param rotation  Rotation type
 * @return Tile     Rotated tile
 */
Tile Tile::rotate(Rotation rotation) const {
    auto rotatedValues = std::map<Edge, std::vector<int>>(); // create a new map of edges
    auto backup = std::vector<int>(E * V); // create a backup of the values
    for (int i = 0; i < E; i++) {
        auto side = (Edge) i; // cast int to Edge enum
        auto sideValues = this->valuesByEdge.at(side); // get the values of the current side
        for (int j = 0; j < V; j++) {
            backup[i * V + j] = sideValues[j]; // backup the values using a 1D array
        }
    }
    if (rotation == Rotation::CLOCKWISE) { // rotate the values clockwise 
        int i = 0;
        for (Edge s : { Edge::RIGHT, Edge::BOTTOM, Edge::LEFT, Edge::TOP }) {
            rotatedValues[s] = { backup[i], backup[i + 1], backup[i + 2] };
            i += 3;
        }
    } else { // rotate the values counterclockwise
        int i = 0;
        for (Edge s : { Edge::LEFT, Edge::TOP, Edge::RIGHT, Edge::BOTTOM }) {
            rotatedValues[s] = { backup[i], backup[i + 1], backup[i + 2] };
            i += 3;
        }
    }
    return Tile(rotatedValues);
}

/**
 * @brief Convert a tile to its multiline string representation.
 * This function converts a tile to its multiline string representation. It is used to print the tile to the terminal.
 * 
 * @param n  nth line of the tile's multiline string representation
 * @return std::string  String representation of the tile
 */
std::string Tile::toLine(const int n) const {
    auto valuesAsStrings = std::vector<std::string>(E * V);
    // convert the values to strings
    for (int i = 0; i < E; i++) {
        Edge side = (Edge) i;
        auto values = this->valuesByEdge.at(side);
        for (int j = 0; j < V; j++) {
            valuesAsStrings[i * V + j] = std::to_string(values[j]);
        }
    }
    switch (n) { // return the nth line of the tile's multiline string representation
        case 0: // top edge
            return " " + valuesAsStrings[0] + " " + valuesAsStrings[1] + " " + valuesAsStrings[2];
        case 1: // first value of the left edge and first value of the right edge
            return valuesAsStrings[9] + "     " + valuesAsStrings[3]; 
        case 2: // second value of the left edge and second value of the right edge
            return valuesAsStrings[10] + "     " + valuesAsStrings[4];
        case 3: // third value of the left edge and third value of the right edge
            return valuesAsStrings[11] + "     " + valuesAsStrings[5];
        case 4: // bottom edge
            return " " + valuesAsStrings[6] + " " + valuesAsStrings[7] + " " + valuesAsStrings[8];
        default:
            return "";
    }
}

/**
 * @brief Overload the << operator for the Tile class
 * This function overloads the << operator for the Tile class. It is used to print the tile to the terminal.
 * 
 * @param stream
 * @param tile 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& stream, const Tile& tile) {
    for (int i = 0; i < L; i++) {
        stream << tile.toLine(i) << std::endl;
    }
    return stream;
}

/**
 * @brief Overload the == operator for the Tile class
 * This function overloads the == operator for the Tile class. It is used to compare two tiles.
 * It compares the values of each edge of the tile.
 * 
 * @param tile1
 * @param tile2 
 * @return true 
 * @return false 
 */
bool operator==(const Tile& tile1, const Tile& tile2) {
    for (int i = 0; i < E; i++) {
        auto side = (Edge) i;
        auto values1 = tile1.valuesByEdge.at(side);
        auto values2 = tile2.valuesByEdge.at(side);
        for (int j = 0; j < V; j++) {
            if (values1[j] != values2[j]) {
                return false;
            }
        }
    }
    return true;
}

