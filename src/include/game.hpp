#pragma once

#include "proto/game.hpp"
#include "proto/trax.hpp"
#include "proto/dominos.hpp"

#include "common.hpp"
#include "board.hpp"
#include "tile.hpp"
#include "interface.hpp"

template <class T, class B, class I> class Game {
    protected:
        B board;
        I interface;
        std::map<int, std::pair<std::string, int>> scoreboard;
        int currentPlayer;
        T currentTile;

    public:
        Game(UserInterfaceProperties, BoardProperties);
        
        void setTile(int x, int y, const T& tile) {
            board.setTile(x, y, tile);
        }

        Option<T> getTile(int x, int y) {
            return board.getTile(x, y);
        }
        
        virtual void run() = 0;
        virtual void handleEvent(const sf::Event&, sf::RenderWindow*) = 0;
};