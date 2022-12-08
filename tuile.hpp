#ifndef __TUILE_HPP__
#define __TUILE_HPP__

#include "common.hpp"

class Tuile {
private:
    std::vector<std::vector<int>> values;

public:
    Tuile();
    friend std::ostream& operator<<(std::ostream& os, const Tuile& t);
}; 

#endif
