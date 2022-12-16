#include "include/dominos.hpp"
#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/common.hpp"

#include <SFML/Graphics.hpp>

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

void DominosTile::draw(sf::RenderWindow& window, const sf::Vector2i& position, const sf::Vector2i& size) {
    // TODO
}

DominosBoard::DominosBoard(int width, int height) : Board(width, height) {
    tiles = std::map<std::pair<int, int>, DominosTile>();
}

DominosBoard::DominosBoard(const DominosBoard& board) : Board(board) {
    this->width = board.width;
    this->height = board.height;
    this->tiles = board.tiles;
}

void DominosBoard::draw(sf::RenderWindow& window, const sf::Vector2i& position) {
    // TODO
}