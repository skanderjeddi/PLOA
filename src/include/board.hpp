#pragma once

#include "proto/common.hpp"
#include "proto/tile.hpp"
#include "proto/board.hpp"

template <class T> class Board {
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
        virtual bool canSet(const T&, const std::pair<int, int>&) const = 0;
        virtual void draw(sf::RenderWindow&, const sf::Vector2i&, const sf::Font&) = 0;
        Board& operator=(const Board&);
};