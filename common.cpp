#include "common.hpp"

std::string printTilesToTerminal(std::map<int, std::map<int, Tile>> sortedByY, std::pair<int, int> infs, std::pair<int, int> sups, int y, int k) {
    auto line = std::string();
    auto linesWithY = sortedByY[y];
    // print all y values
    for (int x = 0; x <= sups.first - infs.first; x++) {
        if (linesWithY.find(x) != linesWithY.end()) {
            line += linesWithY[x].toLine(k) + "\t";
        } else {
            line += "        ";
        }
    }
    return line;
}

int randomInRange(int min, int max) {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float randomIn01() {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0);
    return dist(rng);
}