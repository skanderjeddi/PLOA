#include "include/common.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

template <class S> Option<S>::Option() {
    this->valueSet = false;
}

template <class S> Option<S>::Option(const S& value) : someValue(value) {
    this->valueSet = true;
}

template <class S> const S& Option<S>::unwrap() const {
    return this->someValue;
}

template <class S> bool Option<S>::hasValue() const {
    return this->valueSet;
}

int random(int min, int max) {
    return min + (rand() % (max - min + 1));
}

template class Option<DominosTile>;
template class Option<TraxTile>;
template class Option<CarcassonneTile>;