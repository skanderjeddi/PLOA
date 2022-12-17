#pragma once

#include <SFML/Graphics.hpp>

#include "proto/interface.hpp"

struct UserInterfaceProperties {
    std::string windowTitle;
    sf::Vector2i tileSize;
    sf::Font font;
    sf::Vector2i margin;
};

template <class B, class T> class UserInterface {
    protected:
        UserInterfaceProperties properties;
        BoardProperties boardProperties;
        sf::RenderWindow window;
        std::vector<sf::Drawable*> toRender;

    public:
        UserInterface(UserInterfaceProperties&, BoardProperties&);
        virtual void draw(B&) = 0;
        virtual void drawGrid() = 0;
        virtual void drawBoard(B&) = 0;
        virtual void drawTile(T&, const sf::Vector2i&) = 0;
        void show(B&);
        UserInterfaceProperties getProperties() const { return properties; }
        sf::RenderWindow* getWindow() { return &window; }
        std::vector<sf::Drawable*> renderables() { return toRender; }
};
