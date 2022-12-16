#pragma once

#include "proto/game.hpp"
#include "proto/trax.hpp"
#include "proto/dominos.hpp"

#include "common.hpp"
#include "board.hpp"
#include "tile.hpp"
#include "interface.hpp"

template <class I> class Game {
    protected:
        const sf::Vector2i& tileSize;
        const sf::Font& font;

        std::map<int, std::pair<std::string, int>> scoreboard;
        I& interface;
        int currentPlayer;

    public:
        Game(const sf::Vector2i&, const sf::Font&);
        virtual I& configure() = 0;
        virtual void run() = 0;
        virtual void nextTurn() = 0;
};