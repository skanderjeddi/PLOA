#include "include/dominos.hpp"
#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/common.hpp"
#include "include/interface.hpp"

#include <SFML/Graphics.hpp>

/**
 * ------------
 * DOMINOS TILE
 * ------------
 */

DominosTile::DominosTile() : Tile() {
    properties = std::map<TileEdge, std::vector<int>>();
    for (auto side : { TileEdge::LEFT, TileEdge::TOP, TileEdge::RIGHT, TileEdge::BOTTOM }) {
        properties[side] = std::vector<int>(3);
        for (int i = 0; i < 3; i++) {
            properties[side][i] = random(0, 4);
        }
    }
}

DominosTile::DominosTile(const DominosTile& tile) : Tile(tile) {
    properties = tile.properties;
}

DominosTile::DominosTile(const std::map<TileEdge, std::vector<int>>& properties) : Tile(properties) {
    this->properties = properties;
}

void DominosTile::rotate(const TileRotation& rotation) {
    switch (rotation) {
        case TileRotation::CLOCKWISE:
            properties = std::map<TileEdge, std::vector<int>>({
                { TileEdge::LEFT, properties[TileEdge::BOTTOM] },
                { TileEdge::TOP, properties[TileEdge::LEFT] },
                { TileEdge::RIGHT, properties[TileEdge::TOP] },
                { TileEdge::BOTTOM, properties[TileEdge::RIGHT] }
            });
            break;
        case TileRotation::COUNTERCLOCKWISE:
            properties = std::map<TileEdge, std::vector<int>>({
                { TileEdge::LEFT, properties[TileEdge::TOP] },
                { TileEdge::TOP, properties[TileEdge::RIGHT] },
                { TileEdge::RIGHT, properties[TileEdge::BOTTOM] },
                { TileEdge::BOTTOM, properties[TileEdge::LEFT] }
            });
            break;
    }
}

/**
 * -------------
 * DOMINOS BOARD
 * -------------
 */

DominosBoard::DominosBoard(BoardProperties& properties) : Board(properties) { }

bool DominosBoard::canSet(const DominosTile& tile, const std::pair<int, int>& position) const {
    bool canSet = true;
    if (tiles.find(position) != tiles.end()) {
        return false;
    }
    auto neighbors = getNeighbors(position);
    if (neighbors.size() == 0) {
        return false;
    }
    for (auto neighbor : neighbors) {
        auto edge = neighbor.first;
        auto neighborTile = neighbor.second;
        auto neighborEdge = oppositeEdge(edge);
        auto tileProperties = tile.dataStructure();
        auto neighborTileProperties = neighborTile.dataStructure();
        for (int i = 0; i < 3; i++) {
            if (tileProperties.at(edge)[i] != neighborTileProperties.at(neighborEdge)[i]) {
                canSet = false;
                break;
            }
        }
        if (!canSet) {
            break;
        }
    }
    return canSet;
}

/**
 * -----------------
 * DOMINOS INTERFACE
 * -----------------
 */

DominosInterface::DominosInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) { }

void DominosInterface::draw(DominosBoard& board) {
    drawBoard(board);
}

void DominosInterface::drawBoard(DominosBoard& board) {
    drawGrid(window, properties.tileSize, sf::Vector2i(board.getProperties().width, board.getProperties().height));
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            auto optTile = board.getTile(x, y);
            if (optTile.hasValue()) {
                std::cout << "Tile at" << x << ", " << y << std::endl;
                auto tile = optTile.unwrap();
                drawTile(tile, sf::Vector2i(x * properties.tileSize.x, y * properties.tileSize.y));
            }
        }
    } 
}

void DominosInterface::drawTile(DominosTile& tile, const sf::Vector2i& position) {
    auto tileSize = properties.tileSize;
    auto corners = std::vector<sf::RectangleShape>(4);
    for (int i = 0; i < 4; i++) {
        corners[i] = sf::RectangleShape(sf::Vector2f(tileSize.x / 5, tileSize.y / 5));
        corners[i].setFillColor(sf::Color::Black);
        corners[i].setOutlineColor(sf::Color::Black);
        corners[i].setOutlineThickness(1);
    }
    corners[0].setPosition(position.x + 1, position.y + 1);
    corners[1].setPosition(position.x + tileSize.x - tileSize.x / 5, position.y + 1);
    corners[2].setPosition(position.x + 1, position.y + tileSize.y - tileSize.y / 5 - 1);
    corners[3].setPosition(position.x + tileSize.x - tileSize.x / 5, position.y + tileSize.y - tileSize.y / 5 - 1);
    for (auto corner : corners) {
        window.draw(corner);
    }
    std::vector<sf::RectangleShape> tileRectangles;
    std::vector<sf::Text> tileTexts;
    for (int i = 0; i < 4; i++) {
        auto edge = static_cast<TileEdge>(i);
        auto values = tile.dataStructure().at(edge);
        for (int i = 0; i < 3; i++) {
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(tileSize.x / 5, tileSize.y / 5));
            switch (edge) {
                case TileEdge::TOP:
                    rectangle.setPosition(position.x + (i + 1) * tileSize.x / 5, position.y + 1);
                    break;
                case TileEdge::RIGHT:
                    rectangle.setPosition(position.x + tileSize.x - tileSize.x / 5, position.y + (i + 1) * tileSize.y / 5);
                    break;
                case TileEdge::BOTTOM:
                    rectangle.setPosition(position.x + (i + 1) * tileSize.x / 5, position.y + tileSize.y - tileSize.y / 5 - 1);
                    break;
                case TileEdge::LEFT:
                    rectangle.setPosition(position.x + 1, position.y + (i + 1) * tileSize.y / 5);
                    break;
            }
            auto value = values[i];
            auto text = sf::Text();
            text.setFont(properties.font);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::Black);
            text.setString(std::to_string(value));
            auto textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f, rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
            tileTexts.push_back(text);
            tileRectangles.push_back(rectangle);
        }
    }
    for (auto rectangle : tileRectangles) {
        window.draw(rectangle);
    }
    for (auto text : tileTexts) {
        window.draw(text);
    }
}

void DominosInterface::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        window.setSize(sf::Vector2u(properties.tileSize.x * boardProperties.width, properties.tileSize.y * boardProperties.height));
    }
}

/**
 * -------
 * DOMINOS
 * -------
 */

Dominos::Dominos(UserInterfaceProperties properties, BoardProperties boardProperties) : Game(properties, boardProperties) { }

void Dominos::run() {
    _interface.show(_board);
}

DominosBoard Dominos::board() {
    return _board;
}