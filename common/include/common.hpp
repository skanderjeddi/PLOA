#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <bits/stdc++.h>
#include <map>

#include "tile.hpp"
#include "board.hpp"

/**
 * @brief This common header file contains all the common functions and definitions used in the project that don't really fit anywhere else.
 * Also used to avoid circular dependencies.
 */

#define DEBUG true

template <typename S> class Option {
    private:
        bool hasValue;
        S value;
    public:
        Option() : hasValue(false) {}
        Option(S value) : hasValue(true), value(value) {}
        bool isSome() const { return hasValue; }
        S unwrap() const { return value; }
};

int randomInt(int, int);
float randomFloat();
Edge getOppositeSide(const Edge&);
std::string tilesToString(std::map<int, std::map<int, Tile>>, std::pair<int, int>, std::pair<int, int>, std::pair<int, int>);
std::ostream &operator<<(std::ostream&, const Edge&);

#endif