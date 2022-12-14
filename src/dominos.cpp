#include "include/dominos.hpp"

DominosWindow::DominosWindow(Dominos& game, const std::pair<int, int>& tileSize) : gameInstance(game), tileSize(tileSize) {
    globalFont = sf::Font();
    globalFont.loadFromFile("assets/font.ttf");
}

void DominosWindow::drawBackground(sf::RenderWindow& window, std::vector<sf::RectangleShape>& rectangles) {
    auto width = tileSize.first;
    auto height = tileSize.second;
    if (rectangles.size() == 0) {
        for (int x = 0; x < gameInstance.board.getWidth(); x++) {
            for (int y = 0; y < gameInstance.board.getHeight(); y++) {
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(width, height));
                rectangle.setOutlineColor(sf::Color::White);
                rectangle.setFillColor(sf::Color::Black);
                rectangle.setOutlineThickness(1);
                rectangle.setPosition(x * width + 1, y * height + 1);
                rectangles.push_back(rectangle);
            }
        }
    }
    for (auto rectangle : rectangles) {
        window.draw(rectangle);
    }
}

void DominosWindow::drawTileCorners(sf::RenderWindow& window, const std::pair<int, int>& position, sf::Color color) {
    auto tileWidth = tileSize.first;
    auto tileHeight = tileSize.second;
    auto tileX = position.first;
    auto tileY = position.second;
    std::vector<sf::RectangleShape> corners(4);
    auto cornerSize = sf::Vector2f(tileWidth / 5, tileHeight / 5);
    for (auto& corner : corners) {
        corner.setSize(cornerSize);
        corner.setFillColor(color);
    }
    corners[0].setPosition(tileX, tileY);
    corners[1].setPosition(tileX + tileWidth - tileWidth / 5, tileY);
    corners[2].setPosition(tileX, tileY + tileHeight - tileHeight / 5);    
    corners[3].setPosition(tileX + tileWidth - tileWidth / 5, tileY + tileHeight - tileHeight / 5);
    for (auto corner : corners) {
        window.draw(corner);
    }
}

void DominosWindow::drawTile(sf::RenderWindow& window, const Tile& tile, const std::pair<int, int>& position) {
    auto tileWidth = tileSize.first;
    auto tileHeight = tileSize.second;
    auto tileX = position.first;
    auto tileY = position.second;
    std::vector<sf::RectangleShape> tileRectangles;
    std::vector<sf::Text> tileTexts;
    for (int i = 0; i < 4; i++) {
        auto side = static_cast<Side>(i);
        auto values = tile.getSide(side);
        for (int i = 0; i < 3; i++) {
            // Create rectangle
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(tileWidth / 5, tileHeight / 5));
            rectangle.setFillColor(sf::Color::Black);
            switch (side) {
                case Side::TOP:
                    rectangle.setPosition(tileX + (i + 1) * tileWidth / 5, tileY + 1);
                    break;
                case Side::RIGHT:
                    rectangle.setPosition(tileX + tileWidth - tileWidth / 5, tileY + (i + 1) * tileHeight / 5);
                    break;
                case Side::BOTTOM:
                    rectangle.setPosition(tileX + (i + 1) * tileWidth / 5, tileY + tileHeight - tileHeight / 5 - 1);
                    break;
                case Side::LEFT:
                    rectangle.setPosition(tileX + 1, tileY + (i + 1) * tileHeight / 5);
                    break;
            }
            auto value = values[i];
            auto text = sf::Text();
            text.setFont(globalFont);
            text.setCharacterSize(18);
            text.setFillColor(sf::Color::White);
            text.setString(std::to_string(value));
            auto textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.0f, rectangle.getPosition().y + rectangle.getSize().y / 2.0f);
            tileTexts.push_back(text);
            tileRectangles.push_back(rectangle);
        }
    }
    drawTileCorners(window, position, sf::Color::White);
    for (auto rectangle : tileRectangles) {
        window.draw(rectangle);
    }
    for (auto text : tileTexts) {
        window.draw(text);
    }
}

void DominosWindow::drawBoard(sf::RenderWindow& window) {
    auto board = gameInstance.board;
    auto boardWidth = board.getWidth();
    auto boardHeight = board.getHeight();
    for (int i = 0; i < boardWidth; i++) {
        for (int j = 0; j < boardHeight; j++) {
            auto tile = board.getTile(std::make_pair(i, j));
            if (tile != nullptr) {
                auto position = std::make_pair(tileSize.first * i, tileSize.second * j);
                drawTile(window, *tile, position);
            }
        }
    }
}

int DominosWindow::drawScoreboard(sf::RenderWindow& window) {
    auto board = gameInstance.board;
    auto windowWidth = board.getWidth() * tileSize.first;
    auto columnWidth = windowWidth / 5;
    // Calculate column height
    auto columnHeight = 0;
    columnHeight += tileSize.second;
    columnHeight += (tileSize.second / 3.5f) * gameInstance.scoreboard.size();
    auto column = sf::RectangleShape();
    column.setSize(sf::Vector2f(columnWidth - 1, columnHeight - 1));
    // Outline column and fill with white
    column.setOutlineColor(sf::Color::White);
    column.setFillColor(sf::Color::Black);
    column.setOutlineThickness(1);
    // Draw column
    column.setPosition(windowWidth + 2, 1);
    window.draw(column);
    // Draw scoreboard title
    auto text = sf::Text();
    text.setFont(globalFont);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setString("Scoreboard");
    auto textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(column.getPosition().x + column.getSize().x / 2.0f, column.getPosition().y + tileSize.second / 3.0f);
    window.draw(text);
    std::vector<std::pair<std::string, int>> sortedScoreboard;
    for (auto score : gameInstance.scoreboard) {
        sortedScoreboard.push_back(score.second);
    }
    sort(sortedScoreboard.begin(), sortedScoreboard.end(), [](const std::pair<std::string, int>& pts1, const std::pair<std::string, int>& pts2) {
        return pts1.second > pts2.second;
    });
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    // Draw scoreboard entries aligned at the center of the column
    for (size_t i = 0; i < sortedScoreboard.size(); i++) {
        auto entry = sortedScoreboard[i];
        text.setString(entry.first + ": " + std::to_string(entry.second));
        textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
        text.setPosition(column.getPosition().x + column.getSize().x / 2.0f, column.getPosition().y + tileSize.second / 2.0f + (i + 1) * tileSize.second / 3.5f);
        window.draw(text);
    }
    return columnHeight;
}

int DominosWindow::drawCurrentTile(sf::RenderWindow& window, int scoreboardHeight) {
    auto board = gameInstance.board;
    auto windowWidth = board.getWidth() * tileSize.first;
    auto columnWidth = windowWidth / 5;
    auto columnHeight = 2 * tileSize.second + tileSize.second / 4.0f;
    // Draw column
    auto column = sf::RectangleShape();
    column.setSize(sf::Vector2f(columnWidth - 1, columnHeight - 1));
    column.setOutlineColor(sf::Color::White);
    column.setFillColor(sf::Color::Black);
    column.setOutlineThickness(1);
    column.setPosition(windowWidth + 2, scoreboardHeight);
    window.draw(column);
    // Draw "Current player" centered at the top of the column
    auto text = sf::Text();
    text.setFont(globalFont);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setString("Current player");
    auto textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(windowWidth + columnWidth / 2.0f, scoreboardHeight + tileSize.second / 3.0f);
    window.draw(text);
    // Draw current player's name
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    auto playerName = gameInstance.scoreboard.at(gameInstance.currentPlayerId).first;
    text.setString(playerName);
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(windowWidth + columnWidth / 2.0f, scoreboardHeight + tileSize.second / 1.5f);
    window.draw(text);
    // Draw current player's tile
    auto tile = gameInstance.currentTile;
    auto position = std::make_pair(windowWidth + columnWidth / 2.0f - tileSize.first / 2.0f, scoreboardHeight + tileSize.second);
    drawTile(window, tile, position);
    return scoreboardHeight + columnHeight;
}

void DominosWindow::drawInstructions(sf::RenderWindow& window, int currentTileHeight) {
    auto board = gameInstance.board;
    auto windowWidth = board.getWidth() * tileSize.first;
    auto columnWidth = windowWidth / 5;
    // column height is from current tile height to the bottom of the window
    auto columnHeight = window.getSize().y - currentTileHeight - tileSize.second * 1.4f;
    // Draw column
    auto column = sf::RectangleShape();
    column.setSize(sf::Vector2f(columnWidth - 1, columnHeight - 1));
    column.setOutlineColor(sf::Color::White);
    column.setFillColor(sf::Color::Black);
    column.setOutlineThickness(1);
    column.setPosition(windowWidth + 2, currentTileHeight);
    window.draw(column);
    // Draw "Instructions" centered at the top of the column
    auto text = sf::Text();
    text.setFont(globalFont);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setString("Instructions");
    auto textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + tileSize.second / 3.0f);
    window.draw(text);
    // Draw instructions
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setString("Click on a square");
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + tileSize.second / 1.2f);
    window.draw(text);
    text.setString("to place the tile");
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + tileSize.second / 1.2f + tileSize.second / 4.0f);
    window.draw(text);
    // Draw "Press LEFT or RIGHT"
    text.setString("Press LEFT or RIGHT");
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + tileSize.second / 1.2f + tileSize.second);
    window.draw(text);
    text.setString("to rotate the tile");
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + tileSize.second / 1.2f + tileSize.second + tileSize.second / 4.0f);
    window.draw(text);
    // Draw "Press SPACE to pass"
    text.setString("Press SPACE to pass");
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + tileSize.second / 1.2f + tileSize.second * 2);
    window.draw(text);
    // Draw a new column under the previous column
    sf::RectangleShape column2;
    auto lastColumnHeight = window.getSize().y - columnHeight - currentTileHeight;
    column2.setSize(sf::Vector2f(columnWidth - 1, lastColumnHeight - 1));
    column2.setOutlineColor(sf::Color::White);
    column2.setFillColor(sf::Color::Black);
    column2.setOutlineThickness(1);
    column2.setPosition(windowWidth + 2, currentTileHeight + columnHeight);
    window.draw(column2);
    // Draw "Tiles left: " + number of tiles left
    text.setCharacterSize(26);
    text.setFillColor(sf::Color::White);
    text.setString("Tiles left: " + std::to_string(gameInstance.bag.size()));
    textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(1 + windowWidth + columnWidth / 2.0f, currentTileHeight + columnHeight + lastColumnHeight / 2.0f);
    window.draw(text);
}

void DominosWindow::display() {
    auto board = gameInstance.board;
    auto windowWidth = board.getWidth() * tileSize.first;
    windowWidth += windowWidth / 5;
    auto window_height = board.getHeight() * tileSize.second;
    sf::RenderWindow window(sf::VideoMode(windowWidth, window_height), "Dominos", sf::Style::Close);
    auto background = std::vector<sf::RectangleShape>();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mouse_position = sf::Mouse::getPosition(window);
                    auto x = mouse_position.x / tileSize.first;
                    auto y = mouse_position.y / tileSize.second;
                    auto position = std::make_pair(x, y);
                    if (x < board.getWidth() && y < board.getHeight()) {
                        gameInstance.handlePoints(position);
                        gameInstance.currentPlayerId += 1 % gameInstance.scoreboard.size();
                        gameInstance.nextTurn();
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    gameInstance.currentTile = gameInstance.currentTile.rotate(Rotation::COUNTERCLOCKWISE);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    gameInstance.currentTile = gameInstance.currentTile.rotate(Rotation::CLOCKWISE);
                }
                if (event.key.code == sf::Keyboard::Space) {
                    gameInstance.currentPlayerId += 1;
                    gameInstance.currentPlayerId %= gameInstance.maxPlayers;
                    gameInstance.nextTurn();
                }
            }
        }
        window.clear(sf::Color::White);
        drawBackground(window, background);
        drawBoard(window);
        auto scoreboardHeight = drawScoreboard(window);
        auto currentTileHeight = drawCurrentTile(window, scoreboardHeight);
        drawInstructions(window, currentTileHeight);
        window.display();
    }
}

void Dominos::play() {
    // cout << "Welcome to Domino's!" << endl;
    maxPlayers = registerPlayers();
    currentPlayerId = randomInt(0, maxPlayers - 1);
    nextTurn();
    auto ui = DominosWindow(*this, std::make_pair(100, 100));
    ui.display();
}

int Dominos::registerPlayers() {
    /** auto maxPlayers = 0;
    while (maxPlayers < 2 || maxPlayers > 8) {
        cout << endl << "> How many players? (2-8) ";
        cin >> maxPlayers;
    }**/
    for (int i = 0; i < 4; i++) {
        scoreboard[i] = std::make_pair("Player " + std::to_string(i), 0);
    }
    return 4;
}

void Dominos::nextTurn() {
    auto playerName = scoreboard[currentPlayerId].first;
    float r = randomFloat(0, 1);
    if (r > 0.965) {
        currentTile = board.fitNewTile();
    } else {
        auto random_tile_index = randomInt(0, bag.size() - 1);
        currentTile = bag[random_tile_index];
        bag.erase(bag.begin() + random_tile_index);
    }
}

void Dominos::handlePoints(const std::pair<int, int>& coords) {
    if (board.canPlaceTile(currentTile, coords)) {
        board.placeTile(currentTile, coords);
        auto adjacentTiles = board.gatherAdjacentTiles(coords);
        auto pointsGained = 0;
        for (auto adjacent : adjacentTiles) {
            for (int i = 0; i < 4; i++) {
                pointsGained += 2 * currentTile.getSide(adjacent.first)[i];
            }
        }
        this->scoreboard[currentPlayerId].second += pointsGained;
    } 
}

/** void Dominos::announce_scores(bool is_game_over) {
    std::vector<std::pair<std::string, int>> sortedScoreboard;
    for (auto score : this->scoreboard) {
        sortedScoreboard.push_back(score.second);
    }
    sort(sortedScoreboard.begin(), sortedScoreboard.end(), [](const std::pair<std::string, int>& pts1, const std::pair<std::string, int>& pts2) {
        return pts1.second > pts2.second;
    });
    // TODO
} **/