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

using namespace std;

int randomInt(int, int);
float randomFloat();
Edge getOppositeSide(const Edge&);
string tilesToString(map<int, map<int, Tile>>, pair<int, int>, pair<int, int>, pair<int, int>);
ostream &operator<<(ostream&, const Edge&);

#endif