#ifndef __BOARD_HPP__
#define __BOARD_HPP__

class Board {
    private:
        std::map<std::pair<int, int>, Tile> tilesMap;
        friend class Tile;

    public:
        Board(Tile initialTile);
        std::vector<Tile> generateRandomTiles(int);
        std::vector<std::pair<Side, Tile>> getNeighbors(const int, const int) const;
        bool canPlaceTile(Tile, const int, const int) const;
        void placeTile(Tile, const int, const int);
        Tile retrieveTile(const int, const int) const;
        Side getOppositeSide(Side) const;
        Side findFreeNeighboringSide(const std::vector<Side>) const; 
        Tile findAppropriateTile() const;
        Tile getInitialTile() const;
        friend std::ostream& operator<<(std::ostream&, const Board&);
};

#endif