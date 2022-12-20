#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/common.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"

#include "include/trax.hpp"

#include <SFML/Graphics.hpp>

/**
 * ---------
 * TRAX TILE
 * ---------
 */

TraxTile::TraxTile() : Tile() {
    auto face = random(0, 1) == 0 ? TraxTileFace::HEADS : TraxTileFace::TAILS;
    properties = std::make_pair(face, std::map<TileEdge, TraxTileEdge>());
    properties.second[TileEdge::LEFT] = face == TraxTileFace::HEADS ? TraxTileEdge::WHITE : TraxTileEdge::BLACK;
    properties.second[TileEdge::TOP] = face == TraxTileFace::HEADS ? TraxTileEdge::BLACK : TraxTileEdge::WHITE;
    properties.second[TileEdge::RIGHT] = TraxTileEdge::WHITE;
    properties.second[TileEdge::BOTTOM] = TraxTileEdge::BLACK;
}

TraxTile::TraxTile(const TraxTile& tile) : Tile(tile) {
    properties = tile.properties;
}

TraxTile::TraxTile(const std::pair<TraxTileFace, std::map<TileEdge, TraxTileEdge>>& properties) : Tile(properties) {
    this->properties = properties;
}

void TraxTile::rotate(const TileRotation& rotation) {
    switch (rotation) {
        case TileRotation::CLOCKWISE:
            properties.second = std::map<TileEdge, TraxTileEdge>({
                { TileEdge::LEFT, properties.second[TileEdge::BOTTOM] },
                { TileEdge::TOP, properties.second[TileEdge::LEFT] },
                { TileEdge::RIGHT, properties.second[TileEdge::TOP] },
                { TileEdge::BOTTOM, properties.second[TileEdge::RIGHT] }
            });
            break;
        case TileRotation::COUNTERCLOCKWISE:
            properties.second = std::map<TileEdge, TraxTileEdge>({
                { TileEdge::LEFT, properties.second[TileEdge::TOP] },
                { TileEdge::TOP, properties.second[TileEdge::RIGHT] },
                { TileEdge::RIGHT, properties.second[TileEdge::BOTTOM] },
                { TileEdge::BOTTOM, properties.second[TileEdge::LEFT] }
            });
            break;
    }
}

/**
 * ----------
 * TRAX BOARD
 * ----------
 */

TraxBoard::TraxBoard() : Board(BoardProperties(8, 8)) {
    tiles = std::map<std::pair<int, int>, TraxTile>();
}

TraxBoard::TraxBoard(BoardProperties& properties) : Board(BoardProperties(8, 8)) {
    tiles = std::map<std::pair<int, int>, TraxTile>();
}

bool TraxBoard::canSet(const TraxTile& tile, const std::pair<int, int>& position) const {
    // TODO
    return true;
}

int TraxBoard::handleTile(const TraxTile& tile, const std::pair<int, int>& position) {
    return 0;
}

/**
 * --------------
 * TRAX INTERFACE
 * --------------
 */

TraxInterface::TraxInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) { }

void TraxInterface::draw(TraxBoard& board) { }

void TraxInterface::drawBoard(TraxBoard& board, const sf::Vector2i& position) {
    drawGrid(position);
    // TODO
}

void TraxInterface::drawTile(TraxTile& tile, const sf::Vector2i& position, const sf::Vector2i& offset) {
    // TODO
}

/**
 * ----
 * TRAX
 * ----
 */

Trax::Trax(UserInterfaceProperties properties) : Game(properties, BoardProperties(8, 8)) { }

void Trax::run() {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    interface.show(board);
    sf::RenderWindow* window = interface.getWindow();
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            handleEvent(event, window);
        }
        window->clear(sf::Color::White);
        interface.draw(board);
        interface.drawTile(currentTile, sf::Vector2i(uiProperties.tileSize.x * boardProperties.width + uiProperties.tileSize.x / 2, uiProperties.tileSize.y / 2));
        interface.render();
        window->display();
    }
}

void Trax::handleEvent(const sf::Event& event, sf::RenderWindow* windowPtr) {
    // auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    if (event.type == sf::Event::Resized) {
        windowPtr->setSize(sf::Vector2u(uiProperties.windowSize.x, uiProperties.windowSize.y));
    }
}