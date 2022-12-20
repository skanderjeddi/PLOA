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
            properties[side][i] = random(0, 1);
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
        if (DEBUG) std::cout << "Can set tile!" << std::endl;
        if (DEBUG) std::cout << "Can set tile!" << std::endl;
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
    } else {
        return -1;
    }
}

/**
 * -----------------
 * DOMINOS INTERFACE
 * -----------------
 */

DominosInterface::DominosInterface(UserInterfaceProperties& properties, BoardProperties& boardProperties) : UserInterface(properties, boardProperties) {
    if (boardProperties.width > DOMINOS_BOARD_WIDTH) {
        throw std::invalid_argument("Board width is too large");
    }
    if (boardProperties.height > DOMINOS_BOARD_HEIGHT) {
        throw std::invalid_argument("Board height is too large");
    }
    properties.windowSize = sf::Vector2i(DOMINOS_BOARD_WIDTH, DOMINOS_BOARD_HEIGHT);
    properties.tileSize = sf::Vector2i(DOMINOS_TILE_SIZE, DOMINOS_TILE_SIZE);
}

void DominosInterface::draw(DominosBoard& board) {
    if (DEBUG) std::cout << "Drawing board..." << std::endl;
    // Find coordinates to center the board 
    int x = (properties.windowSize.x - (boardProperties.width + 2) * properties.tileSize.x) / 2;
    int y = (properties.windowSize.y - (boardProperties.height + 1) * properties.tileSize.y) / 2;
    drawBoard(board, sf::Vector2i(x, y));
}

void DominosInterface::drawBoard(DominosBoard& board, const sf::Vector2i& position) {
    if (DEBUG) std::cout << "Drawing grid..." << std::endl;
    drawGrid(position);
    for (int x = 0; x < boardProperties.width; x++) {
        for (int y = 0; y < boardProperties.height; y++) {
            auto optTile = board.getTile(x, y);
            if (optTile.hasValue()) {
                auto tile = optTile.unwrap();
                if (DEBUG) std::cout << "Drawing tile at (" << x << ", " << y << ")" << std::endl;
                drawTile(tile, sf::Vector2i(x * properties.tileSize.x, y * properties.tileSize.y), position);
            }
        }
    } 
}

void DominosInterface::drawTile(DominosTile& tile, const sf::Vector2i& position, const sf::Vector2i& offset) {
    auto tileSize = properties.tileSize;
    auto corners = std::vector<sf::RectangleShape*>(4);
    for (int i = 0; i < 4; i++) {
        corners[i] = new sf::RectangleShape(sf::Vector2f(tileSize.x / 5, tileSize.y / 5));
        corners[i]->setFillColor(sf::Color::Black);
        corners[i]->setOutlineColor(sf::Color::Black);
        corners[i]->setOutlineThickness(1);
    }
    corners[0]->setPosition(offset.x + position.x + 1, offset.y + position.y + 1);
    corners[1]->setPosition(offset.x + position.x + tileSize.x - tileSize.x / 5, offset.y + position.y + 1);
    corners[2]->setPosition(offset.x + position.x + 1, offset.y + position.y + tileSize.y - tileSize.y / 5 - 1);
    corners[3]->setPosition(offset.x + position.x + tileSize.x - tileSize.x / 5, offset.y + position.y + tileSize.y - tileSize.y / 5 - 1);
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
                    rectangle->setPosition(offset.x + position.x + (i + 1) * tileSize.x / 5, offset.y + position.y + 1);
                    break;
                case TileEdge::RIGHT:
                    rectangle->setPosition(offset.x + position.x + tileSize.x - tileSize.x / 5, offset.y + position.y + (i + 1) * tileSize.y / 5);
                    break;
                case TileEdge::BOTTOM:
                    rectangle->setPosition(offset.x + position.x + (i + 1) * tileSize.x / 5, offset.y + position.y + tileSize.y - tileSize.y / 5 - 1);
                    break;
                case TileEdge::LEFT:
                    rectangle->setPosition(offset.x + position.x + 1, offset.y + position.y + (i + 1) * tileSize.y / 5);
                    break;
            }
            auto value = values[i];
            auto text = new sf::Text();
            text->setFont(properties.font);
            text->setCharacterSize(14);
            text->setFillColor(sf::Color::Black);
            text->setString(std::to_string(value));
            auto textBounds = text->getLocalBounds();
            text->setOrigin(textBounds.left + textBounds.width / 2.0, textBounds.top + textBounds.height / 2.0);
            text->setPosition((int) (rectangle->getPosition().x + rectangle->getSize().x / 2.0f), (int) (rectangle->getPosition().y + rectangle->getSize().y / 2.0f));
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

Dominos::Dominos(UserInterfaceProperties properties, BoardProperties boardProperties, int tilesInBag) : Game(properties, boardProperties), remainingTiles(tilesInBag) {
    currentTile = DominosTile();
    currentPlayer = 0;
}

void Dominos::drawMainGame() {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();

    int tileWidth = uiProperties.tileSize.x;
    int tileHeight = uiProperties.tileSize.y;

    int windowWidth = uiProperties.windowSize.x;
    int windowHeight = uiProperties.windowSize.y;

    interface.draw(board);
    // Draw the current player's name and score
    std::string currentPlayerName = scoreboard[currentPlayer].first + (" (" + std::to_string(scoreboard[currentPlayer].second) + "pts)");
    interface.drawText(currentPlayerName, sf::Vector2f(windowWidth - 2 * tileWidth, 0), sf::Vector2f(tileWidth * 2, windowHeight / 10), 21);
    // Draw scoreboard
    interface.drawText("Scoreboard", sf::Vector2f(windowWidth - 2 * tileWidth, 0), sf::Vector2f(tileWidth * 2, (int) (windowHeight / 1.5f)), 21);
    // Sort scoreboard
    auto scores = std::vector<std::pair<int, int>>();
    for (auto score : scoreboard) {
        scores.push_back(std::make_pair(score.first, score.second.second));
    }
    std::sort(scores.begin(), scores.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second > b.second;
    });
    for (size_t i = 0; i < scores.size(); i++) {
        auto playerAndScore = scores[i];
        auto mapEntry = scoreboard[scores[i].first];
        std::string playerName = mapEntry.first + (" - " + std::to_string(mapEntry.second) + "pts");
        interface.drawText(playerName, sf::Vector2f(windowWidth - 2 * tileWidth, 0), sf::Vector2f(tileWidth * 2, (int) (windowHeight / 1.45f) + (int) (windowHeight / 1.45f) / 16 * (i + 1)), 16);
    }
    // Draw the remaining tiles
    std::string remainingTilesStr = "Tuiles restantes: " + std::to_string(remainingTiles);
    interface.drawText(remainingTilesStr, sf::Vector2f(tileWidth * boardProperties.width, windowHeight - tileHeight * 3), sf::Vector2f(tileWidth * 2, tileHeight * 3), 16);
    // Draw instructions
    std::string instructions = "Appuyez sur 'R' pour tourner la tuile, 'Espace' pour passer votre tour";
    // Draw instructions at the bottom of the screen
    interface.drawText(instructions, sf::Vector2f(0, windowHeight - tileHeight), sf::Vector2f(windowWidth, tileHeight), 20);
    // Draw the current tile
    interface.drawTile(currentTile, sf::Vector2i(windowWidth - 2 * tileWidth + tileWidth / 2, windowHeight / 12));
}

void Dominos::drawGameOver() {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    std::string gameOverText = "La partie est finie!";
    interface.drawText(gameOverText, sf::Vector2f(uiProperties.windowSize.x / 2 - uiProperties.tileSize.x, uiProperties.windowSize.y / 2 - uiProperties.tileSize.y), sf::Vector2f(uiProperties.tileSize.x * 2, uiProperties.tileSize.y), 32);
    std::string winnerText = "Le gagnant est: " + scoreboard[0].first + " avec " + std::to_string(scoreboard[0].second) + " points!";
    interface.drawText(winnerText, sf::Vector2f(uiProperties.windowSize.x / 2 - uiProperties.tileSize.x, uiProperties.windowSize.y / 2), sf::Vector2f(uiProperties.tileSize.x * 2, uiProperties.tileSize.y), 32);
    std::string instructions = "Appuyez sur n'importe quel touche pour quitter";
    // Draw instructions at the bottom of the screen
    interface.drawText(instructions, sf::Vector2f(0, uiProperties.windowSize.y - uiProperties.tileSize.y), sf::Vector2f(uiProperties.windowSize.x, uiProperties.tileSize.y), 22);
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
        // Draw the current player's name and score
        std::string currentPlayerName = scoreboard[currentPlayer].first + (" (" + std::to_string(scoreboard[currentPlayer].second) + ")");
        interface.drawText(currentPlayerName, sf::Vector2f(uiProperties.windowSize.x - 2 * uiProperties.tileSize.x, 0), sf::Vector2f(uiProperties.tileSize.x * 2, uiProperties.tileSize.y), 22);
        std::string remainingTilesStr = "Remaining tiles: " + std::to_string(remainingTiles);
        interface.drawText(remainingTilesStr, sf::Vector2f(uiProperties.tileSize.x * boardProperties.width, uiProperties.tileSize.y * 2), sf::Vector2f(uiProperties.tileSize.x * 2, uiProperties.tileSize.y), 18);
        std::string instructions = "Press 'RIGHT' to rotate the tile clockwise, 'LEFT' to rotate the tile counterclockwise, 'SPACE' to pass your turn";
        // Draw instructions at the bottom of the screen
        interface.drawText(instructions, sf::Vector2f(0, uiProperties.windowSize.y - uiProperties.tileSize.y), sf::Vector2f(uiProperties.windowSize.x, uiProperties.tileSize.y), 20);
        interface.drawTile(currentTile, sf::Vector2i(uiProperties.windowSize.x - 2 * uiProperties.tileSize.x + uiProperties.tileSize.x / 2, uiProperties.tileSize.y));
        interface.render();
        window->display();
    }
}

void Dominos::handleEvent(const sf::Event & event, sf::RenderWindow * windowPtr) {
    auto boardProperties = board.getProperties();
    auto uiProperties = interface.getProperties();
    int boardOffsetX = (uiProperties.windowSize.x - (boardProperties.width + 2) * uiProperties.tileSize.x) / 2;
    int boardOffsetY = (uiProperties.windowSize.y - (boardProperties.height + 1) * uiProperties.tileSize.y) / 2;
    if (event.type == sf::Event::Resized) {
        windowPtr->setSize(sf::Vector2u(uiProperties.windowSize.x, uiProperties.windowSize.y));
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        if (!isGameOver) {
            auto mousePosition = sf::Mouse::getPosition(*windowPtr);
            auto x = (mousePosition.x - boardOffsetX) / uiProperties.tileSize.x;
            auto y = (mousePosition.y - boardOffsetY) / uiProperties.tileSize.y;
            auto position = std::make_pair(x, y);
            if (x < boardProperties.width && y < boardProperties.height) {
                std::cout << "inside tile: " << x << ", " << y << std::endl;
                int result = board.handleTile(currentTile, position);
                if (result != -1) {
                    std::cout << "+ " << result << " points" << std::endl;
                    scoreboard[currentPlayer].second += result;
                    currentPlayer += 1;
                    currentPlayer %= scoreboard.size();
                    currentTile = DominosTile();
                    remainingTiles -= 1;
                    if (remainingTiles == 0) {
                        isGameOver = true;
                    }
                }
            }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (!isGameOver) {
            if (event.key.code == sf::Keyboard::R) {
                currentTile.rotate(TileRotation::CLOCKWISE);
            } else if (event.key.code == sf::Keyboard::Space) {
                currentPlayer += 1;
                currentPlayer %= scoreboard.size();
                currentTile = DominosTile();
                remainingTiles -= 1;
                if (remainingTiles == 0) {
                    isGameOver = true;
                }
            }
        } else {
            if (event.type == sf::Event::KeyPressed) {
                // TODO
            }
        }
    }
}