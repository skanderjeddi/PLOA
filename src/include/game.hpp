#pragma once

#include "proto/game.hpp"
#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"
#include "interface.hpp"

template <class T, class B, class I>
class Game
{
protected:
    B board;
    I interface;
    std::map<int,
             std::pair<std::string,
                       int>>
        scoreboard;
    int currentPlayer;
    T *currentTile;
    bool isGameOver = false;

public:
    /**
     * @brief Construct a new Game object with the given properties.
     *
     * @param UserInterfaceProperties the properties of the interface.
     * @param BoardProperties the properties of the board.
     */
    Game(UserInterfaceProperties, BoardProperties);
    /**
     * @brief Handle an event.
     *
     * @param sf::Event the event to handle.
     * @param sf::RenderWindow a pointer to the window to handle the event in.
     */
    virtual void handleEvent(const sf::Event &, sf::RenderWindow *) = 0;

    virtual void drawGameScreen() = 0;
    virtual void drawGameOverScreen() = 0;

    /**
     * @brief called on update
     *
     */
    void run()
    {
        interface.show(board);
        sf::RenderWindow *window = interface.getWindow();
        window->setKeyRepeatEnabled(false);
        while (window->isOpen())
        {
            sf::Event event;
            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                }
                handleEvent(event, window);
            }
            window->clear(sf::Color(0x171B22));
            if (!isGameOver)
            {
                drawGameScreen();
            }
            else
            {
                drawGameOverScreen();
            }
            interface.render();
            window->display();
        }
    }
    /**
     * @brief Register a player.
     *
     * @param name the name of the player.
     */
    void registerPlayer(const std::string &name)
    {
        scoreboard[scoreboard.size()] = std::make_pair(name, 0);
    }
    /**
     * @brief Get the Scoreboard object
     *
     * @return std::map<int, std::pair<std::string, int>>& the scoreboard.
     */
    std::map<int,
             std::pair<std::string,
                       int>> &
    getScoreboard()
    {
        return scoreboard;
    }
    /**
     * @brief Set the Tile object on the board at the given coordinates.
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @param tile the tile to set.
     */
    void setTile(int x, int y,
                 const T &tile)
    {
        board.setTile(x, y, tile);
    }
    /**
     * @brief Get the Tile object at the given coordinates if there is one.
     *
     * @param x x coordinate.
     * @param y y coordinate.
     * @return Option<T> the tile at the given coordinates, or an empty Option if there is none.
     */
    T *getTile(int x, int y)
    {
        return board.getTile(x, y);
    }
};