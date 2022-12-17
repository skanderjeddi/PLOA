#include <SFML/Graphics.hpp>

#include "include/common.hpp"
#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"

template <class B, class T> UserInterface<B, T>::UserInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : properties(properties), boardProperties(boardProperties) { }

template <class B, class T> void UserInterface<B, T>::show(B& board) {
    window.create(sf::VideoMode(properties.tileSize.x * boardProperties.width, properties.tileSize.y * boardProperties.height), properties.windowTitle, sf::Style::Close);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleEvent(event);
        }
        window.clear(sf::Color::White);
        draw(board);
        window.display();
    }
}

void drawGrid(sf::RenderWindow& window, const sf::Vector2i& tileSize, const sf::Vector2i& boardSize) {
    sf::RectangleShape line(sf::Vector2f(tileSize.x * boardSize.x, 1));
    line.setOutlineColor(sf::Color::Black);
    line.setFillColor(sf::Color::Black);
    for (int i = 0; i <= boardSize.y; i++) {
        line.setPosition(0, i * tileSize.y);
        window.draw(line);
    }
    line.setSize(sf::Vector2f(1, tileSize.y * boardSize.y));
    for (int i = 0; i <= boardSize.x; i++) {
        line.setPosition(i * tileSize.x, 0);
        window.draw(line);
    }
}

template class UserInterface<DominosBoard, DominosTile>;
template class UserInterface<TraxBoard, TraxTile>;
