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
        std::vector<std::pair<sf::Drawable*, bool>> toRender;

    public:
        UserInterface(UserInterfaceProperties&, BoardProperties&);
        virtual void draw(B&) = 0;
        void drawText(std::string, const sf::Vector2f&, const sf::Vector2f&, int);
        virtual void drawGrid() = 0;
        virtual void drawBoard(B&) = 0;
        virtual void drawTile(T&, const sf::Vector2i&) = 0;
        void show(B&);
        void registerForRendering(sf::Drawable* ptr, bool b) { toRender.push_back(std::make_pair(ptr, b)); }
        UserInterfaceProperties getProperties() const { return properties; }
        sf::RenderWindow* getWindow() { return &window; }
        std::vector<std::pair<sf::Drawable*, bool>> renderables() { return toRender; }
};
