#pragma once

#include "proto/common.hpp"
#include "proto/tile.hpp"
#include "proto/board.hpp"

struct BoardProperties {
    int width, height;

    BoardProperties(int w, int h) : width(w), height(h) {
        
    } 
};

template <class T> class Board {
    protected:
        const BoardProperties properties;
        std::map<std::pair<int, int>, T> tiles;

    public:
        Board(const BoardProperties&);
        Board(const Board&);
        Option<T> getTile(int, int) const;
        void setTile(int, int, const T&);
        std::vector<std::pair<TileEdge, T>> getNeighbors(const std::pair<int, int>&) const;
        virtual bool canSet(const T&, const std::pair<int, int>&) const = 0;
        BoardProperties getProperties() const { return properties; } 
};