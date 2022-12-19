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

DominosBoard::DominosBoard(BoardProperties& properties) : Board(properties) {
    this->setTile(properties.width / 2, properties.height / 2, DominosTile());
}

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

int DominosBoard::handleTile(const DominosTile& tile, const std::pair<int, int>& position) {
    if (canSet(tile, position)) {
        this->tiles[position] = tile;
        auto neighbors = getNeighbors(position);
        int count = 0;
        for (auto neighbor : neighbors) {
            for (auto edge : { TileEdge::TOP, TileEdge::RIGHT, TileEdge::BOTTOM, TileEdge::LEFT }) {
                if (edge == neighbor.first) {
                    for (auto value : neighbor.second.dataStructure().at(oppositeEdge(edge))) count += 2 * value;
                }
            }
        }
        return count;
    }
    return 0;
}

/**
 * -----------------
 * DOMINOS INTERFACE
 * -----------------
 */

DominosInterface::DominosInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) { }

void DominosInterface::draw(DominosBoard& board) {
    if (DEBUG) std::cout << "Drawing board..." << std::endl;
    drawBoard(board);
}

void DominosInterface::drawGrid() {
    std::vector<sf::RectangleShape*> rectangles;
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            sf::RectangleShape* tile = new sf::RectangleShape(sf::Vector2f(properties.tileSize.x - 1, properties.tileSize.y - 1));
            if (DEBUG) std::cout << "New rectangle @ " << tile << std::endl;
            tile->setOutlineColor(sf::Color::Black);
            tile->setOutlineThickness(1);
            tile->setFillColor(sf::Color::Transparent);     
            tile->setPosition(x * properties.tileSize.x + 1, y * properties.tileSize.y + 1);
            rectangles.push_back(tile);
        }
    }
    for (auto rect : rectangles) {
        registerForRendering(rect);
    }
}

void DominosInterface::drawBoard(DominosBoard& board) {
    if (DEBUG) std::cout << "Drawing grid..." << std::endl;
    drawGrid();
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            auto optTile = board.getTile(x, y);
            if (optTile.hasValue()) {
                auto tile = optTile.unwrap();
                if (DEBUG) std::cout << "Drawing tile at (" << x << ", " << y << ")" << std::endl;
                drawTile(tile, sf::Vector2i(x * properties.tileSize.x, y * properties.tileSize.y));
            }
        }
    } 
}

void DominosInterface::drawTile(DominosTile& tile, const sf::Vector2i& position) {
    auto tileSize = properties.tileSize;
    auto corners = std::vector<sf::RectangleShape*>(4);
    for (int i = 0; i < 4; i++) {
        corners[i] = new sf::RectangleShape(sf::Vector2f(tileSize.x / 5, tileSize.y / 5));
        corners[i]->setFillColor(sf::Color::Black);
        corners[i]->setOutlineColor(sf::Color::Black);
        corners[i]->setOutlineThickness(1);
    }
    corners[0]->setPosition(position.x + 1, position.y + 1);
    corners[1]->setPosition(position.x + tileSize.x - tileSize.x / 5, position.y + 1);
    corners[2]->setPosition(position.x + 1, position.y + tileSize.y - tileSize.y / 5 - 1);
    corners[3]->setPosition(position.x + tileSize.x - tileSize.x / 5, position.y + tileSize.y - tileSize.y / 5 - 1);
    for (auto corner : corners) {
        registerForRendering(corner);
    }
    std::vector<sf::RectangleShape*> tileRectangles;
    std::vector<sf::Text*> tileTexts;
    for (int i = 0; i < 4; i++) {
        auto edge = static_cast<TileEdge>(i);
        auto values = tile.dataStructure().at(edge);
        for (int i = 0; i < 3; i++) {
            sf::RectangleShape* rectangle = new sf::RectangleShape();
            rectangle->setSize(sf::Vector2f(tileSize.x / 5, tileSize.y / 5));
            switch (edge) {
                case TileEdge::TOP:
                    rectangle->setPosition(position.x + (i + 1) * tileSize.x / 5, position.y + 1);
                    break;
                case TileEdge::RIGHT:
                    rectangle->setPosition(position.x + tileSize.x - tileSize.x / 5, position.y + (i + 1) * tileSize.y / 5);
                    break;
                case TileEdge::BOTTOM:
                    rectangle->setPosition(position.x + (i + 1) * tileSize.x / 5, position.y + tileSize.y - tileSize.y / 5 - 1);
                    break;
                case TileEdge::LEFT:
                    rectangle->setPosition(position.x + 1, position.y + (i + 1) * tileSize.y / 5);
                    break;
            }
            auto value = values[i];
            auto text = new sf::Text();
            text->setFont(properties.font);
            text->setCharacterSize(14);
            text->setFillColor(sf::Color::Black);
            text->setString(std::to_string(value));
            auto textBounds = text->getLocalBounds();
            text->setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            text->setPosition(rectangle->getPosition().x + rectangle->getSize().x / 2.0f, rectangle->getPosition().y + rectangle->getSize().y / 2.0f);
            tileTexts.push_back(text);
            tileRectangles.push_back(rectangle);
        }
    }
    for (auto rectangle : tileRectangles) {
        registerForRendering(rectangle);
    }
    for (auto text : tileTexts) {
        registerForRendering(text);
    }
}

/**
 * -------
 * DOMINOS
 * -------
 */

Dominos::Dominos(UserInterfaceProperties properties, BoardProperties boardProperties) : Game(properties, boardProperties) {
    currentTile = DominosTile();
    currentPlayer = 0;
}

void Dominos::run() {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    interface.show(board);
    sf::RenderWindow* window = interface.getWindow();
    window->setKeyRepeatEnabled(false);
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
        std::string currentPlayerName = scoreboard[currentPlayer].first + (" (" + std::to_string(scoreboard[currentPlayer].second) + ")");
        interface.drawText(currentPlayerName, sf::Vector2f(uiProperties.tileSize.x * boardProperties.width, 0), sf::Vector2f(uiProperties.tileSize.x * 2, uiProperties.tileSize.y), 16);
        std::string instructions = "Press 'RIGHT' to rotate the tile clockwise, 'LEFT' to rotate the tile counterclockwise, 'SPACE' to pass your turn";
        // Draw instructions at the bottom of the screen
        interface.drawText(instructions, sf::Vector2f(0, uiProperties.tileSize.y * boardProperties.height), sf::Vector2f(uiProperties.tileSize.x * boardProperties.width + uiProperties.margin.x, uiProperties.tileSize.y), 22);
        interface.drawTile(currentTile, sf::Vector2i(uiProperties.tileSize.x * boardProperties.width + uiProperties.tileSize.x / 2, uiProperties.tileSize.y));
        interface.render();
        window->display();
    }
}

void Dominos::handleEvent(const sf::Event& event, sf::RenderWindow* windowPtr) {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    if (event.type == sf::Event::Resized) {
        windowPtr->setSize(sf::Vector2u(uiProperties.tileSize.x * boardProperties.width + uiProperties.margin.x, uiProperties.tileSize.y * boardProperties.height + uiProperties.margin.y));
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        auto mousePosition = sf::Mouse::getPosition(*windowPtr);
        auto x = mousePosition.x / uiProperties.tileSize.x;
        auto y = mousePosition.y / uiProperties.tileSize.y;
        auto position = std::make_pair(x, y);
        if (x < boardProperties.width && y < boardProperties.height) {
            scoreboard[currentPlayer].second += board.handleTile(currentTile, position);
            currentPlayer += 1;
            currentPlayer %= scoreboard.size();
            currentTile = DominosTile();
            // TODO: game over
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
            currentTile.rotate(TileRotation::CLOCKWISE);
        } else if (event.key.code == sf::Keyboard::Left) {
            currentTile.rotate(TileRotation::COUNTERCLOCKWISE);
        } else if (event.key.code == sf::Keyboard::Space) {
            currentTile = DominosTile();
        }
    }
}