#include "include/tile.hpp"
#include "include/common.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

#include <SFML/Graphics.hpp>

template <class P>
Tile<P>::Tile()
{
    properties = P();
}

template <class P>
Tile<P>::Tile(const Tile &tile)
{
    properties = tile.properties;
}

template <class P>
Tile<P>::Tile(const P &value)
{
    this->properties = properties;
}

template <class P>
const P &Tile<P>::dataStructure() const
{
    return properties;
}

TileEdge oppositeEdge(const TileEdge &edge)
{
    TileEdge opposite;
    switch (edge)
    {
    case TileEdge::LEFT:
        opposite = TileEdge::RIGHT;
        break;
    case TileEdge::TOP:
        opposite = TileEdge::BOTTOM;
        break;
    case TileEdge::RIGHT:
        opposite = TileEdge::LEFT;
        break;
    case TileEdge::BOTTOM:
        opposite = TileEdge::TOP;
        break;
    }
    return opposite;
}

template class Tile<std::map<TileEdge, std::vector<int>>>;
template class Tile<std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>>;
template class Tile<std::map<TileEdge, CarcassonneTileType>>;