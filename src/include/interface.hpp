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
        void drawText(std::string, const sf::Vector2f&, const sf::Vector2f&, int);
        virtual void drawGrid() = 0;
        virtual void drawBoard(B&) = 0;
        virtual void drawTile(T&, const sf::Vector2i&) = 0;
        void show(B&);
        void registerForRendering(sf::Drawable* ptr) {
            if (DEBUG) std::cout << "Registering " << ptr << " for rendering..." << std::endl;
            toRender.push_back(ptr);
        }
        void render() {
            for (size_t i = 0; i < toRender.size(); i++) {
                window.draw(*toRender[i]);
            }
            for (size_t i = 0; i < toRender.size(); i++) {
                if (DEBUG) std::cout << "Deleting " << toRender[i] << " ..." << std::endl;
                delete toRender[i];
                toRender.erase(toRender.begin() + i);
            }
        }
        UserInterfaceProperties getProperties() const { return properties; }
        sf::RenderWindow* getWindow() { return &window; }
};
