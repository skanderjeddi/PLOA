#pragma once

#include "proto/dominos.hpp"

#include "board.hpp"
#include "tile.hpp"
#include "common.hpp"

class DominosWindow {
    private:
        Dominos& gameInstance;
        const std::pair<int, int> tileSize;
        sf::Font globalFont;
        void drawBackground(sf::RenderWindow&, std::vector<sf::RectangleShape>&);
        void drawTileCorners(sf::RenderWindow&, const std::pair<int, int>&, sf::Color);
        void drawTile(sf::RenderWindow&, const Tile&, const std::pair<int, int>&);
        void drawBoard(sf::RenderWindow&);
        int drawScoreboard(sf::RenderWindow&);
        int drawCurrentTile(sf::RenderWindow&, int);
        void drawInstructions(sf::RenderWindow&, int);
    public:
        DominosWindow(Dominos&, const std::pair<int, int>&);
        void display();
        // Override = operator
        DominosWindow& operator=(const DominosWindow& other) {
            return *this;
        }
};

class Dominos {
    private:
        Board board;
        int currentPlayerId;
        Tile currentTile;
        int maxPlayers;
        std::vector<Tile> bag;
        std::map<int, std::pair<std::string, int>> scoreboard;        
        void registerPlayers(const int);
        bool nextTurn();
        void handlePoints(const std::pair<int, int>&);
        friend class Board;
        friend class DominosWindow;
    public:
        Dominos(const std::pair<int, int>& dimensions, int tilesInBag) : board(dimensions.first, dimensions.second), bag(tilesInBag) {};
        void play(const std::pair<int, int>&, const int);
};

