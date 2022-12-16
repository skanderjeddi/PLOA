#include "include/tile.hpp"
#include "include/common.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"

#include <SFML/Graphics.hpp>

template <class P> Tile<P>::Tile() {
    properties = P();
}

template <class P> Tile<P>::Tile(const Tile& tile) {
    properties = tile.properties;
}

template <class P> Tile<P>::Tile(const P& value) {
    this->properties = properties;
}

template <class P> const P& Tile<P>::dataStructure() const {
    return properties;
}

template class Tile<std::map<TileEdge, std::vector<int>>>;
template class Tile<std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>>;