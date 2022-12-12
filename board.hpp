#ifndef __BOARD_HPP__
#define __BOARD_HPP__

class Board {
    private:
        std::map<std::pair<int, int>, Tile> tilesMap;
        friend class Tile;

    public:
        Board(Tile initialTile);
        std::vector<std::pair<Side, Tile>> getNeighbors(const int x, const int y) const;
        bool canPlaceTile(Tile new_tile, const int x, const int y) const;
        void placeTile(Tile new_tile, const int x, const int y);
        Side getOppositeSide(Side) const;
        Side findFreeNeighboringSide(const std::vector<Side>) const; 
        Tile findAppropriateTile() const;
        friend std::ostream& operator<<(std::ostream& stream, const Board& board);
};

#endif