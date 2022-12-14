#pragma once

#include "proto/common.hpp"
#include "proto/tile.hpp"

int randomInt(int, int);
float randomFloat(float, float);
Side getOppositeSide(const Side&);
std::ostream &operator<<(std::ostream&, const Side&);