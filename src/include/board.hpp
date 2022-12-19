#pragma once

#include "proto/common.hpp"
#include "proto/tile.hpp"
#include "proto/board.hpp"

struct BoardProperties {
    int width, height;

    BoardProperties(int w, int h) : width(w), height(h) { } 
};

template <class T> class Board {
    protected:
        const BoardProperties properties;
        std::map<std::pair<int, int>, T> tiles;

    public:
        Board(const BoardProperties&);
        Board(const Board&);
        /**
         * @brief Get the Tile object if there is one at the given coordinates.
         * 
         * @return Option<T> the tile at the given coordinates, or an empty Option if there is none.
         */
        Option<T> getTile(int, int) const;
        /**
         * @brief Set the Tile object at the given coordinates.
         */
        void setTile(int, int, const T&);
        /**
         * @brief Handle the tile at the given coordinates.
         * 
         * @return int the points gained by the player who placed the tile.
         */
        virtual int handleTile(const T&, const std::pair<int, int>&) = 0;
        /**
         * @brief Get the Neighbors object of the tile at the given coordinates.
         * 
         * @return std::vector<std::pair<TileEdge, T>> a vector of pairs of the edge of the tile and the tile at that edge if there is one.
         */
        std::vector<std::pair<TileEdge, T>> getNeighbors(const std::pair<int, int>&) const;
        /**
         * @brief Check if the tile can be placed at the given coordinates.
         * 
         * @return true if the tile can be placed at the given coordinates.
         * @return false otherwise.
         */
        virtual bool canSet(const T&, const std::pair<int, int>&) const = 0;
        /**
         * @brief Get the Properties object of the board.
         * 
         * @return BoardProperties 
         */
        BoardProperties getProperties() const { return properties; } 
};