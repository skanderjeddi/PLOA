#include "include/common.hpp"

Tile::Tile() {
    this->valuesByEdge = std::map<Side, std::vector<int>>();
    for (int i = 0; i < EDGES; i++) {
        auto side = (Side) i;
        this->valuesByEdge[side] = std::vector<int>(VALUES);
        for (int value = 0; value < VALUES; value++) {
            // generate a random int between 1 and 6
            auto random = randomInRange(1, 6);
            this->valuesByEdge[side][value] = random;
        }
    }
}

Tile Tile::rotate(Rotation rotation) const {
    auto rotatedValues = std::map<Side, std::vector<int>>();
    auto backup = std::vector<int>(EDGES * VALUES);
    for (int i = 0; i < EDGES; i++) {
        auto side = (Side) i;
        for (int j = 0; j < VALUES; j++) {
            backup[i * VALUES + j] = this->valuesByEdge.at(side)[j];
        }
    }
    if (rotation == Rotation::CLOCKWISE) {
        rotatedValues[Side::TOP] = { backup[9], backup[10], backup[11] };
        rotatedValues[Side::RIGHT] = { backup[0], backup[1], backup[2] };
        rotatedValues[Side::BOTTOM] = { backup[3], backup[4], backup[5] };
        rotatedValues[Side::LEFT] = { backup[6], backup[7], backup[8] };
    } else {
        rotatedValues[Side::BOTTOM] = { backup[9], backup[10], backup[11] };
        rotatedValues[Side::LEFT] = { backup[0], backup[1], backup[2] };
        rotatedValues[Side::TOP] = { backup[3], backup[4], backup[5] };
        rotatedValues[Side::RIGHT] = { backup[6], backup[7], backup[8] };
    }
    return Tile(rotatedValues);
}

std::string Tile::toLine(const int line) const {
    auto valuesAsStrings = std::vector<std::string>(EDGES * VALUES);
    for (int i = 0; i < EDGES; i++) {
        Side side = (Side) i;
        for (int j = 0; j < VALUES; j++) {
            valuesAsStrings[i * VALUES + j] = std::to_string(this->valuesByEdge.at(side)[j]);
        }
    }
    switch (line) {
        case 0:
            return " " + valuesAsStrings[0] + " " + valuesAsStrings[1] + " " + valuesAsStrings[2];
        case 1:
            return valuesAsStrings[9] + "     " + valuesAsStrings[3]; 
        case 2:
            return valuesAsStrings[10] + "     " + valuesAsStrings[4];
        case 3:
            return valuesAsStrings[11] + "     " + valuesAsStrings[5];
        case 4:
            return " " + valuesAsStrings[6] + " " + valuesAsStrings[7] + " " + valuesAsStrings[8];
        default:
            return "";
    }
}

std::ostream& operator<<(std::ostream& stream, const Tile& tile) {
    stream << tile.toLine(0) << std::endl << tile.toLine(1) << std::endl << tile.toLine(2) << std::endl << tile.toLine(3) << std::endl << tile.toLine(4);
    return stream;
}

bool operator==(const Tile& tile1, const Tile& tile2) {
    for (int i = 0; i < EDGES; i++) {
        for (int value = 0; value < VALUES; value++) {
            if (tile1.valuesByEdge.at((Side) i)[value] != tile2.valuesByEdge.at((Side) i)[value]) {
                return false;
            }
        }
    }
    return true;
}

