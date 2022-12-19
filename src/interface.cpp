#include <SFML/Graphics.hpp>

#include "include/common.hpp"
#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

#include "include/dominos.hpp"
#include "include/trax.hpp"

template <class B, class T> UserInterface<B, T>::UserInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : properties(properties), boardProperties(boardProperties) { }

template <class B, class T> void UserInterface<B, T>::show(B& board) {
    window.create(sf::VideoMode(properties.tileSize.x * boardProperties.width + properties.margin.x, properties.tileSize.y * boardProperties.height + properties.margin.y), properties.windowTitle, sf::Style::Close);
}

template <class B, class T> void UserInterface<B, T>::drawText(std::string contents, const sf::Vector2f& position, const sf::Vector2f& size, int fontSize) {
    // Draw text centered in container
    auto container = new sf::RectangleShape(size);
    container->setPosition(position);
    container->setFillColor(sf::Color::Transparent);
    registerForRendering(container);
    auto text = new sf::Text();
    text->setFont(properties.font);
    text->setCharacterSize(fontSize);
    text->setFillColor(sf::Color::Black);
    text->setString(contents);
    auto textBounds = text->getLocalBounds();
    text->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text->setPosition(container->getPosition().x + container->getSize().x / 2.0f, container->getPosition().y + container->getSize().y / 2.0f);
    registerForRendering(text);
}

template class UserInterface<DominosBoard, DominosTile>;
template class UserInterface<TraxBoard, TraxTile>;
