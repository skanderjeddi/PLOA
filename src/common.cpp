#include "include/common.hpp"
#include "include/tile.hpp"

int randomInt(int min, int max) {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float randomFloat(float min, float max) {
    std::random_device rd;
    const long seed = rd();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

Side getOppositeSide(const Side& side) {
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

std::ostream& operator<<(std::ostream& stream, const Side& side) {
    switch (side) {
        case Side::TOP:
            stream << "TOP";
            break;
        case Side::RIGHT:
            stream << "RIGHT";
            break;
        case Side::BOTTOM:
            stream << "BOTTOM";
            break;
        case Side::LEFT:
            stream << "LEFT";
            break;
    }
    return stream;
}