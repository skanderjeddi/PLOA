#include <SFML/Graphics.hpp>

#include "include/common.hpp"
#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

template <class B, class T> UserInterface<B, T>::UserInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : properties(properties), boardProperties(boardProperties) { }

template <class B, class T> void UserInterface<B, T>::show(B& board) {
    window.create(sf::VideoMode(properties.windowSize.x, properties.windowSize.y), properties.windowTitle, sf::Style::Close);
}

template <class B, class T> void UserInterface<B, T>::drawGrid(const sf::Vector2i& position) {
    std::vector<sf::RectangleShape*> rectangles;
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            sf::RectangleShape* tile = new sf::RectangleShape(sf::Vector2f(properties.tileSize.x - 1, properties.tileSize.y - 1));
            if (DEBUG) std::cout << "New rectangle @ " << tile << std::endl;
            tile->setOutlineColor(sf::Color(150, 150, 150, 255));
            tile->setOutlineThickness(1);
            tile->setFillColor(sf::Color::Transparent);     
            tile->setPosition(position.x + x * properties.tileSize.x + 1, position.y + y * properties.tileSize.y + 1);
            rectangles.push_back(tile);
        }
    }
    for (auto rect : rectangles) {
        registerForRendering(rect);
    }
}

template <class B, class T> void UserInterface<B, T>::drawText(std::string contents, const sf::Vector2f& position, const sf::Vector2f& size, int fontSize) {
    // Draw text centered in container
    auto container = new sf::RectangleShape(size);
    container->setPosition(sf::Vector2f((int) position.x, (int) position.y));
    container->setFillColor(sf::Color::Transparent);
    registerForRendering(container);
    auto text = new sf::Text();
    text->setFont(properties.font);
    text->setCharacterSize(fontSize);
    text->setFillColor(sf::Color(150, 150, 150, 255));
    text->setString(contents);
    auto textBounds = text->getLocalBounds();
    text->setOrigin((int) (textBounds.left + textBounds.width / 2.0f), (int) (textBounds.top + textBounds.height / 2.0f));
    text->setPosition((int) (container->getPosition().x + container->getSize().x / 2.0f), (int) (container->getPosition().y + container->getSize().y / 2.0f));
    registerForRendering(text);
}

template class UserInterface<DominosBoard, DominosTile>;
template class UserInterface<TraxBoard, TraxTile>;
template class UserInterface<CarcassonneBoard, CarcassonneTile>;