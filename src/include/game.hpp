#pragma once

#include "proto/game.hpp"
#include "proto/trax.hpp"
#include "proto/dominos.hpp"

#include "common.hpp"
#include "board.hpp"
#include "tile.hpp"
#include "interface.hpp"

template <class B, class I> class Game {
    protected:
        B _board;
        I _interface;
        std::map<int, std::pair<std::string, int>> scoreboard;
        int currentPlayer;

    public:
        Game(UserInterfaceProperties, BoardProperties);
        virtual void run() = 0;
        virtual B board() = 0;
};