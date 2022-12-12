#ifndef __BOARD_HPP__
#define __BOARD_HPP__

/**
 * @brief Board class
 * This class represents the board of the game. It is a map of tiles, where each tile is identified by a pair of integers.
 * The board is responsible for generating random tiles, placing those tiles.
 * It is also responsible for finding the neighbors of a tile, and checking if a tile can be placed on the board.
 * It can find the free neighboring side(s) of a tile.
 * It is responsible for retrieving tiles from the tiles inner map, and for printing the board.
 */

using namespace std;

class Board {
    private:
        map<pair<int, int>, Tile> tilesMap;
        friend class Tile;

    public:
        Board(Tile initialTile, pair<int, int>);
        vector<Tile> generateRandomTiles(int);
        vector<pair<Edge, Tile>> getNeighbors(const int, const int) const;
        bool canPlaceTile(Tile, const int, const int) const;
        void placeTile(Tile, const int, const int);
        Tile retrieveTile(const int, const int) const;
        Edge findFreeEdge(const vector<Edge>) const; 
        Tile findTileThatFits() const;
        Tile getInitialTile() const;
        friend ostream& operator<<(ostream&, const Board&);
};

#endif