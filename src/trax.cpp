#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/common.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"

#include "include/trax.hpp"

#include <SFML/Graphics.hpp>

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

void TraxTile::draw(sf::RenderWindow& window, const sf::Vector2i& position, const sf::Vector2i& size, const sf::Font& font) {
    // TODO
}

TraxBoard::TraxBoard() : Board(8, 8) {
    tiles = std::map<std::pair<int, int>, TraxTile>();
}

TraxBoard::TraxBoard(const TraxBoard& board) : Board(board) {
    this->width = board.width;
    this->height = board.height;
    this->tiles = board.tiles;
}

bool TraxBoard::canSet(const TraxTile& tile, const std::pair<int, int>& position) const {
    // TODO
    return true;
}

void TraxBoard::draw(sf::RenderWindow& window, const sf::Vector2i& position, const sf::Font& font) {
    // TODO
}

void TraxInterface::draw() {
    board.draw(window, sf::Vector2i(0, 0), font);
}

void TraxInterface::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        window.setSize(sf::Vector2u((board.getWidth() + 2) * tileSize.x, board.getHeight() * tileSize.y + 1));
    }
}

Trax::Trax(const sf::Vector2i& tileSize, const sf::Font& font) : Game(tileSize, font) {
    // TODO
}

TraxInterface& Trax::configure() {
    // TODO
}

void Trax::run() {
    // TODO
}

void Trax::nextTurn() {
    // TODO
}