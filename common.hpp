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

#define DEBUG true

std::string printTilesToTerminal(std::map<int, std::map<int, Tile>>, std::pair<int, int>, std::pair<int, int>, int, int);
int randomInRange(int, int);
float randomIn01();

#endif