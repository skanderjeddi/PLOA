#include "common.hpp"
#include "tuile.hpp"

Tuile::Tuile() {
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

std::ostream& operator<<(std::ostream& os, const Tuile& t) {
    for (int side = 0; side < 4; side++) {
        for (int value = 0; value < 3; value++) {
            os << t.values[side][value] << " ";
        }
        os << std::endl;
    }
    return os;
}