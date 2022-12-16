#pragma once

#include "proto/common.hpp"
#include "proto/tile.hpp"
#include "proto/board.hpp"

template <typename T> class Board {
    protected:
        int width, height;
        std::map<std::pair<int, int>, T> tiles;

    public:
        Board(int, int);
        Board(const Board&);
        int getWidth() const;
        int getHeight() const;
        Option<T> getTile(int, int) const;
        void setTile(int, int, const T&);
        std::vector<std::pair<TileEdge, T>> getNeighbors(const std::pair<int, int>&) const;
        virtual void draw(sf::RenderWindow&, const sf::Vector2i&) = 0;
};