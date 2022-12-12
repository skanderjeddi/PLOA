#include "common.hpp"

Tile::Tile() {
    this->values = std::map<Side, std::vector<int>>();
    for (int i = 0; i < 4; i++) {
        auto side = (Side) i;
        this->values[side] = std::vector<int>(3);
        for (int value = 0; value < 3; value++) {
            // generate a random int between 1 and 6
            auto random = random_in_range(1, 6);
            this->values[side][value] = random;
        }
    }
}

Tile Tile::rotate(Rotation rotation) {
    auto new_values = std::map<Side, std::vector<int>>();
    auto temp = std::vector<int>(12);
    for (int i = 0; i < 4; i++) {
        auto side = (Side) i;
        for (int j = 0; j < 3; j++) {
            // Convert i and j to a single array index
            temp[i * 3 + j] = this->values.at(side)[j];
        }
    }
    if (rotation == Rotation::CLOCKWISE) {
        // Rotate clockwise
        new_values[TOP] = { temp[9], temp[10], temp[11] };
        new_values[RIGHT] = { temp[0], temp[1], temp[2] };
        new_values[BOTTOM] = { temp[3], temp[4], temp[5] };
        new_values[LEFT] = { temp[6], temp[7], temp[8] };
    } else { // 9-10-11 = LEFT | 0-1-2 = TOP | 3-4-5 = RIGHT | 6-7-8 = BOTTOM
        new_values[BOTTOM] = { temp[9], temp[10], temp[11] };
        new_values[LEFT] = { temp[0], temp[1], temp[2] };
        new_values[TOP] = { temp[3], temp[4], temp[5] };
        new_values[RIGHT] = { temp[6], temp[7], temp[8] };
    }
    return Tile(new_values);
}

std::string Tile::line_representation(const int line) const {
    // Convert all values in this->values to strings and store them in a vector
    auto strings = std::vector<std::string>(12);
    for (int i = 0; i < 4; i++) {
        Side side = (Side) i;
        for (int j = 0; j < 3; j++) {
            // Convert i and j to a single array index
            strings[i * 3 + j] = std::to_string(this->values.at(side)[j]);
        }
    }
    switch (line) {
        case 0:
            return " " + strings[0] + " " + strings[1] + " " + strings[2];
        case 1:
            return strings[9] + "     " + strings[3]; 
        case 2:
            return strings[10] + "     " + strings[4];
        case 3:
            return strings[11] + "     " + strings[5];
        case 4:
            return " " + strings[6] + " " + strings[7] + " " + strings[8];
        default:
            return "";
    }
}

std::ostream& operator<<(std::ostream& os, const Tile& t) {
    std::cout << t.line_representation(0) << std::endl << t.line_representation(1) << std::endl << t.line_representation(2) << std::endl << t.line_representation(3) << std::endl << t.line_representation(4);
    return os;
}

bool operator==(const Tile& t1, const Tile& t2) {
    for (int i = 0; i < 4; i++) {
        for (int value = 0; value < 3; value++) {
            if (t1.values.at((Side) i)[value] != t2.values.at((Side) i)[value]) {
                return false;
            }
        }
    }
    return true;
}