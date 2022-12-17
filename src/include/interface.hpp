#pragma once

#include <SFML/Graphics.hpp>

#include "proto/interface.hpp"

struct UserInterfaceProperties {
    std::string windowTitle;
    sf::Vector2i tileSize;
    sf::Font font;
};

template <class B, class T> class UserInterface {
    protected:
        UserInterfaceProperties properties;
        BoardProperties boardProperties;
        sf::RenderWindow window;
    public:
        UserInterface(UserInterfaceProperties&, BoardProperties&);
        virtual void draw(B&) = 0;
        virtual void drawBoard(B&) = 0;
        virtual void drawTile(T&, const sf::Vector2i&) = 0;
        void show(B&);
        virtual void handleEvent(const sf::Event&) = 0;
};

void drawGrid(sf::RenderWindow&, const sf::Vector2i&, const sf::Vector2i&);

