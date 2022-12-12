#include "../include/dominos.hpp"

#define DEBUG true

void Dominos::play() {
    play(DEFAULT_PLAYERS, DEFAULT_TILES_IN_BAG, DEFAULT_ATTEMPTS_PER_TILE);
}

void Dominos::play(int players, int tilesInBag, int attemptsPerTile, float luck) {
    greetUser();
    registerPlayers(players);
    std::cout << std::endl << "> The game will now begin!";
    showBoard();
    generateRandomTiles(tilesInBag);
    loopTurns(randomInt(0, players - 1), luck);
}

void Dominos::greetUser() { std::cout << "Welcome to Quadriminos!" << std::endl; }

void Dominos::registerPlayers(int maxPlayers) {
    auto players = std::vector<std::string>(maxPlayers);
    std::cout << std::endl << "> Enter " << maxPlayers << " distinct name(s): " << std::endl;
    for (int i = 0; i < maxPlayers; i++) {
        std::cout << "Player " << i + 1 << "? ";
        std::cin >> players[i];
    }
    auto scores = std::map<int, std::pair<std::string, int>>();
    for (int i = 0; i < maxPlayers; i++) {
        scores[i] = make_pair(players[i], 0);
    }
    this->playersAndScores = scores;
}

void Dominos::showBoard() { std::cout << std::endl << "> Here's the current board:" << std::endl << std::endl << board; }

void Dominos::generateRandomTiles(int number) {
    randomTiles = std::vector<Tile>(number);
    for (int i = 0; i < number; i++) randomTiles[i] = Tile();
}

void Dominos::loopTurns(int firstPlayerId, float luck) {
    int currentPlayer = firstPlayerId;
    while (true) {
        if (randomTiles.size() == 0) {
            std::cout << std::endl << "> There are no more tiles left. The game is over!" << std::endl;
            announceScores(true);
        }
        currentPlayer = nextTurnFor(currentPlayer, luck);
    }
}

int Dominos::nextTurnFor(int playerId, float luck) {
    auto playerName = playersAndScores[playerId].first;
    auto playerScore = playersAndScores[playerId].second;
    std::cout << std::endl << "> It is " << playerName << "'s turn! They currently have " << playerScore << " total points.";
    showBoard();
    Tile tileToPlay;
    float r = randomFloat();
    if (r < luck) {
        std::cout << std::endl << "* " << playerName << " got very lucky and will draw a special tile *";
        tileToPlay = board.findTileThatFits();
    } else {
        auto randomTileIndex = randomInt(0, randomTiles.size() - 1);
        tileToPlay = randomTiles[randomTileIndex];
        randomTiles.erase(randomTiles.begin() + randomTileIndex);
    }
    std::cout << std::endl << "> " << playerName << " has drawn the following tile:" << std::endl;
    std::cout << std::endl << tileToPlay << std::endl;
    std::cout << "Press [K] to rotate the tile clockwise, [L] to rotate the tile counterclockwise.\nPress [P] to place it or [D] to discard it.\nPress [Q] to quit." << std::endl;
    readPlayerInput(playerId, tileToPlay);
    return (playerId + 1) % playersAndScores.size();
}

void Dominos::readPlayerInput(int playerId, Tile& tileToPlay) {
    while (true) {
        std::string input;
        std::cout << std::endl << "> ";
        std::cin >> input;
        if (input == "Q") {
            announceScores(false);
        } else if (input == "K") {
            tileToPlay = tileToPlay.rotate(Rotation::CLOCKWISE);
            std::cout << std::endl << "> Here's your rotated tile:" << std::endl << std::endl << tileToPlay << std::endl;
        } else if (input == "L") {
            tileToPlay = tileToPlay.rotate(Rotation::COUNTERCLOCKWISE);
            std::cout << std::endl << "> Here's your rotated tile:" << std::endl << std::endl << tileToPlay << std::endl;
        } else if (input == "P") {
            auto attempts = 0;
            while (attempts < 3) {
                std::cout << "Where would you like to place it? (Enter the coordinates as x#y, (negative) whole numbers allowed) [" << 3 - attempts << " attempt(s) remaining]" << std::endl;
                auto option = processPlayerInput();
                if (option.isSome()) {
                    attempts--;
                    auto coords = option.unwrap();
                    if (!handlePoints(playerId, tileToPlay, coords)) {
                        if (attempts > 0) {
                            std::cout << "Invalid placement. Please try again." << std::endl;
                            attempts--;
                        } else {
                            std::cout << "You have reached the maximum number of attempts. The tile has been discarded." << std::endl;
                            return;
                        }
                    } else {
                        return;
                    }
                } else {
                    std::cout << "Invalid input. Please try again." << std::endl;
                }
            }
        } else if (input == "D") {
            std::cout << "> You have discarded the tile." << std::endl;
            return;
        } else {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
}

bool Dominos::handlePoints(int playerId, Tile tileToPlay, std::pair<int, int> coords) {
    auto x = coords.first;
    auto y = coords.second;
    std::cout << std::endl << "> You have chosen to place the tile at (" << x << ", " << y << ")." << std::endl;
    if (board.canPlaceTile(tileToPlay, x, y)) {
        std::cout << "> You have successfully placed the tile!" << std::endl;
        board.placeTile(tileToPlay, x, y);
        // Gather neighbors to the placed tile
        auto neighbors = board.getNeighbors(x, y);
        auto pointsGained = 0;
        for (auto neighbor : neighbors) {
            for (int i = 0; i < 4; i++) {
                pointsGained += 2 * tileToPlay.getValues().at(neighbor.first)[i];
            }
        }
        std::cout << "> You have earned " << pointsGained << " points!" << std::endl;
        this->playersAndScores[playerId].second += pointsGained;
        std::cout << "> Your total score is " << this->playersAndScores[playerId].second << "." << std::endl;
        return true;
    } else {
        return false;
    }
}

Option<std::pair<int, int>> Dominos::processPlayerInput() {
    std::string input;
    std::cout << "> ";
    std::cin >> input;
    std::stringstream ss(input);
    std::string token;
    std::vector<std::string> tokens;
    while (getline(ss, token, '#')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 2) {
        return Option<std::pair<int, int>>();
    }
    int x, y;
    bool negX = false, negY = false;
    if (tokens[0].at(0) == '-') {
        negX = true;
        tokens[0] = tokens[0].substr(1);
    }
    if (tokens[1].at(0) == '-') {
        negY = true;
        tokens[1] = tokens[1].substr(1);
    }
    try {
        x = stoi(tokens[0]) * (negX ? -1 : 1);
        y = stoi(tokens[1]) * (negY ? -1 : 1);
    } catch (std::invalid_argument& e) {
        return Option<std::pair<int, int>>();
    }
    return Option<std::pair<int, int>>(std::make_pair(x, y));
}

void Dominos::announceScores(bool gameOver) {
    std::vector<std::pair<std::string, int>> sortedScores;
    for (auto score : this->playersAndScores) {
        sortedScores.push_back(score.second);
    }
    sort(sortedScores.begin(), sortedScores.end(), [](const std::pair<std::string, int>& pts1, const std::pair<std::string, int>& pts2) {
        return pts1.second > pts2.second;
    });
    if (gameOver) {
        std::cout << std::endl << "The game is over! Here are the final scores:" << std::endl;
        int i = 1;
        for (auto score : sortedScores) {
            std::cout << i << ": " << score.first << ": " << score.second << std::endl;
            i++;
        }
        std::cout << std::endl << "Thanks for playing! See you soon!" << std::endl;
        exit(0);
    } else {
        std::cout << std::endl << "The game wasn't completed. Here are the partial results:" << std::endl;
        int i = 1;
        for (auto score : sortedScores) {
            std::cout << i << ": " << score.first << ": " << score.second << std::endl;
            i++;
        }
        std::cout << std::endl << "Thanks for playing! See you soon!" << std::endl;
        exit(0);
    }
}