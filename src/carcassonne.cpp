#include "include/carcassonne.hpp"

/**
 * ----------------
 * CARCASSONNE TILE
 * ----------------
 */

CarcassonneTile::CarcassonneTile() : Tile() {
    properties = std::pair<CarcassonneTileType, std::vector<std::map<CarcassonnePawnType, CarcassonnePawnPlacement>>>();
}

CarcassonneTile::CarcassonneTile(const CarcassonneTile& tile) : Tile(tile) {
    properties = tile.properties;
}

CarcassonneTile::CarcassonneTile(const std::pair<CarcassonneTileType, std::vector<std::map<CarcassonnePawnType, CarcassonnePawnPlacement>>>& properties) : Tile(properties) {
    this->properties = properties;
}

void CarcassonneTile::rotate(const TileRotation& rotation) {
    // TODO
}

/**
 * -------------
 * CARCASSONNE BOARD
 * -------------
 */

CarcassonneBoard::CarcassonneBoard(BoardProperties& properties) : Board(properties) {
    this->setTile(properties.width / 2, properties.height / 2, CarcassonneTile());
}

bool CarcassonneBoard::canSet(const CarcassonneTile& tile, const std::pair<int, int>& position) const {
    // TODO
    return true;
}

int CarcassonneBoard::handleTile(const CarcassonneTile& tile, const std::pair<int, int>& position) {
    return 0;
}

/**
 * -----------------
 * CARCASSONNE INTERFACE
 * -----------------
 */

CarcassonneInterface::CarcassonneInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) {
    // TODO
}

void CarcassonneInterface::draw(CarcassonneBoard& board) {
    if (DEBUG) std::cout << "Drawing board..." << std::endl;
    // Find coordinates to center the board 
    int x = (properties.windowSize.x - (boardProperties.width + 2) * properties.tileSize.x) / 2;
    int y = (properties.windowSize.y - (boardProperties.height + 1) * properties.tileSize.y) / 2;
    drawBoard(board, sf::Vector2i(x, y));
}

void CarcassonneInterface::drawBoard(CarcassonneBoard& board, const sf::Vector2i& position) {
    if (DEBUG) std::cout << "Drawing grid..." << std::endl;
    drawGrid(position);
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            auto optTile = board.getTile(x, y);
            if (optTile.hasValue()) {
                auto tile = optTile.unwrap();
                if (DEBUG) std::cout << "Drawing tile at (" << x << ", " << y << ")" << std::endl;
                // drawTile(tile, sf::Vector2i(x * properties.tileSize.x, y * properties.tileSize.y), position);
            }
        }
    } 
}

void CarcassonneInterface::drawTile(CarcassonneTile& tile, const sf::Vector2i& position, const sf::Vector2i& offset) {
    // TODO
}

/**
 * -------
 * CARCASSONNE
 * -------
 */

Carcassonne::Carcassonne(UserInterfaceProperties properties, BoardProperties boardProperties) : Game(properties, boardProperties) {
    currentTile = CarcassonneTile();
    currentPlayer = 0;
}

void Carcassonne::drawGameScreen() {
    // TODO
}

void Carcassonne::drawGameOverScreen() {
    // TODO
}

void Carcassonne::handleEvent(const sf::Event & event, sf::RenderWindow * windowPtr) {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    int tileWidth = uiProperties.tileSize.x;
    int tileHeight = uiProperties.tileSize.y;
    int windowWidth = uiProperties.windowSize.x;
    int windowHeight = uiProperties.windowSize.y;
    int boardOffsetX = (uiProperties.windowSize.x - (boardProperties.width + 2) * tileWidth) / 2;
    int boardOffsetY = (uiProperties.windowSize.y - (boardProperties.height + 1) * tileHeight) / 2;
    if (event.type == sf::Event::Resized) {
        windowPtr->setSize(sf::Vector2u(windowWidth, windowHeight));
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (!isGameOver) {
            auto mousePosition = sf::Mouse::getPosition(*windowPtr);
            auto x = (mousePosition.x - boardOffsetX) / tileWidth;
            auto y = (mousePosition.y - boardOffsetY) / tileHeight;
            auto position = std::make_pair(x, y);
            if (x < boardProperties.width && y < boardProperties.height) {
                // TODO
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (!isGameOver) {
            // TODO
        } else {
            if (event.type == sf::Event::KeyPressed) {
                // TODO
            }
        }
    }
}