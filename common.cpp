#include "common.hpp"

std::string tiles_to_terminal(std::map<int, std::map<int, Tile>> sorted, std::pair<int, int> mins, std::pair<int, int> maxs, int y, int k) {
    auto line = std::string();
    auto linesWithY = sorted[y];
    // print all y values
    for (int x = 0; x <= mins.first + maxs.first; x++) {
        if (linesWithY.find(x) != linesWithY.end()) {
            line += linesWithY[x].line_representation(k) + "\t";
        } else {
            line += "        ";
        }
    }
    return line;
}

int random_in_range(int min, int max) {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float random_in_0_1_range() {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(rng);
}