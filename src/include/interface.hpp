#pragma once

#include <SFML/Graphics.hpp>

#include "proto/interface.hpp"

struct UserInterfaceProperties {
    std::string windowTitle;
    sf::Vector2i tileSize;
    sf::Vector2i windowSize;
    sf::Font font;
};

template <class B, class T> class UserInterface {
    protected:
        UserInterfaceProperties properties;
        BoardProperties boardProperties;
        sf::RenderWindow window;
        std::vector<sf::Drawable*> toRender;

    public:
        UserInterface(UserInterfaceProperties&, BoardProperties&);
        /**
         * @brief Draws everything on the screen.
         * 
         * @param B& The board to draw.
         */
        virtual void draw(B&) = 0;
        /**
         * @brief Draws text on the screen.
         * 
         * @param std::string The text to draw.
         * @param const sf::Vector2f& The position of the rectangle containing the text in which it will be centered.
         * @param const sf::Vector2f& The size of the rectangle containing the text in which it will be centered.
         * @param int The size of the text.
         */
        void drawText(std::string, const sf::Vector2f&, const sf::Vector2f&, int);
        /**
         * @brief Draws the grid on the screen.
         */
        void drawGrid(const sf::Vector2i& = sf::Vector2i(0, 0));
        /**
         * @brief Draws the board on the screen.
         */
        virtual void drawBoard(B&, const sf::Vector2i& = sf::Vector2i(0, 0)) = 0;
        /**
         * @brief Draws a tile on the screen.
         */
        virtual void drawTile(T&, const sf::Vector2i&, const sf::Vector2i& = sf::Vector2i(0, 0)) = 0;
        /**
         * @brief Shows the interface (i.e. displays the window).
         */
        void show(B&);
        /**
         * @brief Registers a drawable for rendering.
         * 
         * @param ptr a pointer to the drawable to register.
         */
        void registerForRendering(sf::Drawable* ptr) {
            if (DEBUG) std::cout << "Registering " << ptr << " for rendering..." << std::endl;
            toRender.push_back(ptr);
        }
        /**
         * @brief Renders all the drawables registered for rendering then deletes them.
         */
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
        /**
         * @brief Get the Properties object
         * 
         * @return UserInterfaceProperties the UI properties.
         */
        UserInterfaceProperties getProperties() const { return properties; }
        /**
         * @brief Get the Window object
         * 
         * @return sf::RenderWindow* a pointer to the window.
         */
        sf::RenderWindow* getWindow() { return &window; }
};
