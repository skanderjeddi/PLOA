#include "common.hpp"
#include "tile.hpp"

Tile::Tile() {
    std::vector<std::vector<int>> values = std::vector<std::vector<int>>(4, std::vector<int>(3)); 
    for (int side = 0; side < 4; side++) {
        for (int value = 0; value < 3; value++) {
            // generate a random int between 0 and 6
            std::random_device rd;
            const long seed = rd();
            std::mt19937 rng(seed);
            std::uniform_int_distribution<int> dist(1, 6);
            int random = dist(rng);
            values[side][value] = random;
        }
    }
    this->values = values;
}

void Tile::rotate() {
    std::vector<std::vector<int>> new_values = std::vector<std::vector<int>>(4, std::vector<int>(3));
    for (int side = 0; side < 4; side++) {
        for (int value = 0; value < 3; value++) {
            new_values[side][value] = this->values[(side + 3) % 4][value];
        }
    }
    this->values = new_values;
}

std::string Tile::line_repr(const int line) const {
    switch (line) {
        case 0:
            return " " + std::to_string(this->values[TOP][0]) + " " + std::to_string(this->values[TOP][1]) + " " + std::to_string(this->values[TOP][2]);
        case 1:
            return std::to_string(this->values[LEFT][0]) + "     " + std::to_string(this->values[RIGHT][0]);
        case 2:
            return std::to_string(this->values[LEFT][1]) + "     " + std::to_string(this->values[RIGHT][1]);
        case 3:
            return std::to_string(this->values[LEFT][2]) + "     " + std::to_string(this->values[RIGHT][2]);
        case 4:
            return " " + std::to_string(this->values[BOTTOM][0]) + " " + std::to_string(this->values[BOTTOM][1]) + " " + std::to_string(this->values[BOTTOM][2]);
        default:
            return "";
    }
}

std::ostream& operator<<(std::ostream& os, const Tile& t) {
    std::cout << t.line_repr(0) << std::endl << t.line_repr(1) << std::endl << t.line_repr(2) << std::endl << t.line_repr(3) << std::endl << t.line_repr(4);
    return os;
}

bool operator==(const Tile& t1, const Tile& t2) {
    for (int side = 0; side < 4; side++) {
        for (int value = 0; value < 3; value++) {
            if (t1.values[side][value] != t2.values[side][value]) {
                return false;
            }
        }
    }
    return true;
}