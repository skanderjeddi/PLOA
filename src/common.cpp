#include "include/common.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

int random(int min, int max) {
    return min + (rand() % (max - min + 1));
}
