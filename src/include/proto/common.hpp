#pragma once

#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <map>
#include <random>
#include <algorithm>
#include <sstream>
#include <SFML/Graphics.hpp>

#define DEBUG false

/**
 * @brief An option type for C++ copied from Rust.
 * 
 * @tparam S the type of the value
 */
template <class S> class Option;