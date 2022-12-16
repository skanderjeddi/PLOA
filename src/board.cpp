#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/common.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"

template <class T> Board<T>::Board(int width, int height) {
    this->width = width;
    this->height = height;
    this->tiles = std::map<std::pair<int, int>, T>();
}

template <class T> Board<T>::Board(const Board& board) {
    this->width = board.width;
    this->height = board.height;
    this->tiles = board.tiles;
}

template <class T> int Board<T>::getWidth() const {
    return width;
}

template <class T> int Board<T>::getHeight() const {
    return height;
}

template <class T> Option<T> Board<T>::getTile(int x, int y) const {
    if (tiles.find(std::pair<int, int>(x, y)) != tiles.end())
        return Option<T>(tiles.at(std::pair<int, int>(x, y)));
    return Option<T>();
}

template <class T> void Board<T>::setTile(int x, int y, const T& tile) {
    tiles[std::pair<int, int>(x, y)] = tile;
}

template <class T> std::vector<std::pair<TileEdge, T>> Board<T>::getNeighbors(const std::pair<int, int>& pos) const {
    auto positions = std::vector<std::pair<int, int>>({
        std::pair<int, int>(pos.first - 1, pos.second),
        std::pair<int, int>(pos.first, pos.second - 1),
        std::pair<int, int>(pos.first + 1, pos.second),
        std::pair<int, int>(pos.first, pos.second + 1)
    });
    auto neighbors = std::vector<std::pair<TileEdge, T>>();
    for (size_t i = 0; i < positions.size(); i++) {
        auto position = positions[i];
        if (tiles.find(position) != tiles.end())
            neighbors.push_back(std::pair<TileEdge, T>(static_cast<TileEdge>(i), tiles.at(position)));
    }
    return neighbors;
}

template class Board<DominosTile>;
template class Board<TraxTile>;