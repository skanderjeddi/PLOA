#include "include/board.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

template <class T> Board<T>::Board(const BoardProperties& properties) : properties(properties) {
    this->tiles = std::map<std::pair<int, int>, T>();
}

template <class T> Board<T>::Board(const Board& board) : properties(board.properties) {
    this->tiles = board.tiles;
}

template <class T> void Board<T>::setTile(int x, int y, const T& tile) {
    this->tiles[std::make_pair(x, y)] = tile;
}

template <class T> Option<T> Board<T>::getTile(int x, int y) const {
    if (tiles.find(std::make_pair(x, y)) != tiles.end()) {
        return Option<T>(tiles.at(std::make_pair(x, y)));
    }
    return Option<T>();
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
template class Board<CarcassonneTile>;