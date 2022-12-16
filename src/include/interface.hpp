#pragma once

#include <SFML/Graphics.hpp>

#include "proto/interface.hpp"

template <class B> class UserInterface {
    protected:
        B board;
        std::string title;
        sf::RenderWindow window;
        sf::Vector2i tileSize;
        sf::Font font;
    public:
        UserInterface(const B&, const std::string&, const sf::Vector2i&, const sf::Font&);
        void run();
        virtual void draw() = 0;
        virtual void handleEvent(const sf::Event&) = 0;
};

void drawGrid(sf::RenderWindow&, const sf::Vector2i&, const sf::Vector2i&);

