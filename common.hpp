#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <iostream>
#include <vector>
#include <random>
#include <map>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <bits/stdc++.h>

#include "tile.hpp"
#include "board.hpp"

std::string tiles_to_terminal(std::map<int, std::map<int, Tile>> sorted, std::pair<int, int> mins, std::pair<int, int> maxs, int y, int k);
int random_in_range(int, int);

#endif