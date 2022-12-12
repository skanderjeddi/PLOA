#ifndef __DOMINOS_HPP__
#define __DOMINOS_HPP__

#include "../../common/include/common.hpp"

#define DEFAULT_PLAYERS 4
#define DEFAULT_TILES_IN_BAG 30
#define DEFAULT_ATTEMPTS_PER_TILE 3
#define DEFAULT_LUCK 0.05f

class Dominos {
    private:
        Board board;
        std::vector<Tile> randomTiles;
        std::map<int, std::pair<std::string, int>> playersAndScores;
        friend class Board;
        void greetUser();
        void registerPlayers(int);
        void generateRandomTiles(int);
        void showBoard();
        void loopTurns(int, float);
        int nextTurnFor(int, float = DEFAULT_LUCK);
        void readPlayerInput(int, Tile&);
        Option<std::pair<int, int>> processPlayerInput();
        bool handlePoints(int, Tile, std::pair<int, int>);
        void announceScores(bool);
        
    public:
        Dominos() {}
        void play();
        void play(int, int, int, float = DEFAULT_LUCK);
};

#endif