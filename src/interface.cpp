#include <SFML/Graphics.hpp>

#include "include/common.hpp"
#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"

template <class B> UserInterface<B>::UserInterface(const B& board, const std::string& title, const sf::Vector2i& tileSize, const sf::Font& font) : board(board), tileSize(tileSize), font(font) {
    window.create(sf::VideoMode(tileSize.x * board.getWidth(), tileSize.y * board.getHeight()), title, sf::Style::Close);
}

template <class B> void UserInterface<B>::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleEvent(event);
        }
        window.clear(sf::Color::White);
        draw();
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



template class UserInterface<DominosBoard>;
template class UserInterface<TraxBoard>;
