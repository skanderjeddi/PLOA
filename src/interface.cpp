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

template class UserInterface<DominosBoard, DominosTile>;
template class UserInterface<TraxBoard, TraxTile>;
