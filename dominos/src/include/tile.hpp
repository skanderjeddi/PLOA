#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "common.hpp"

#define E 4
#define V 3
#define L 5

/**
 * @brief Edge enum
 * This enum represents the sides of a tile. It is used to identify the edges of a tile.
 */
enum class Edge {
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

/**
 * @brief Rotation enum
 * This enum represents the rotation of a tile. It is used to rotate a tile clockwise or counterclockwise.
 */
enum class Rotation {
    CLOCKWISE,
    COUNTERCLOCKWISE
};

using namespace std;

/**
 * @brief Tile class
 * This class represents a tile in the game. It is a map of edges, where each edge is identified by a Edge enum.
 * Each edge is a vector of integers, where each integer represents a value on the edge.
 * The tile is responsible for rotating itself. It is also responsible for handling its values.
 * It can be compared to another tile through a custom operator==. It can be printed to the terminal.
 */
class Tile {
    private:
        map<Edge, vector<int>> valuesByEdge;
        friend class Board;
    
    public:
        Tile();
        Tile(map<Edge, vector<int>> values) : valuesByEdge(values) {};
        Tile rotate(const Rotation rotation) const;
        string toLine(const int line) const;
        map<Edge, vector<int>> getValues() const { return this->valuesByEdge; };
        friend ostream& operator<<(ostream& stream, const Tile& tile);
        friend bool operator==(const Tile& tile1, const Tile& tile2);
};

#endif
