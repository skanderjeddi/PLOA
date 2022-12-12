#include "../include/dominos.hpp"

#define DEBUG true

using namespace std;

void Dominos::play() {
    play(DEFAULT_PLAYERS, DEFAULT_TILES_IN_BAG, DEFAULT_ATTEMPTS_PER_TILE);
}

void Dominos::play(int players, int tilesInBag, int attemptsPerTile, float luck = DEFAULT_LUCK) {
    greetUser();
    registerPlayers(players);
    cout << endl << "> The game will now begin!";
    showBoard();
    generateRandomTiles(tilesInBag);
    loopTurns(randomInt(0, players - 1), luck);
}

void Dominos::greetUser() { cout << "Thank you for playing Quadriminos!" << endl; }

void Dominos::registerPlayers(int maxPlayers) {
    auto players = vector<string>(maxPlayers);
    cout << endl << "> Enter " << maxPlayers << " distinct name(s): " << endl;
    for (int i = 0; i < maxPlayers; i++) {
        cout << "Player " << i + 1 << "? ";
        cin >> players[i];
    }
    auto scores = map<int, pair<string, int>>();
    for (int i = 0; i < maxPlayers; i++) {
        scores[i] = make_pair(players[i], 0);
    }
    this->playersAndScores = scores;
}

void Dominos::showBoard() { cout << endl << "> Here's the current board:" << endl << endl << board; }

void Dominos::generateRandomTiles(int number) {
    randomTiles = vector<Tile>(number);
    for (int i = 0; i < number; i++) randomTiles[i] = Tile();
}

void Dominos::loopTurns(int firstPlayerId, float luck) {
    int currentPlayer = firstPlayerId;
    while (true) {
        if (randomTiles.size() == 0) {
            cout << endl << "> There are no more tiles left. The game is over!" << endl;
            announceScores(true);
        }
        currentPlayer = nextTurnFor(currentPlayer, luck);
    }
}

int Dominos::nextTurnFor(int playerId, float luck = DEFAULT_LUCK) {
    auto playerName = playersAndScores[playerId].first;
    auto playerScore = playersAndScores[playerId].second;
    cout << endl << "> It is " << playerName << "'s turn! They currently have " << playerScore << " total points.";
    showBoard();
    Tile tileToPlay;
    float r = randomFloat();
    if (r < luck) {
        cout << endl << "* " << playerName << " got very lucky and will draw a special tile *";
        tileToPlay = board.findTileThatFits();
    } else {
        auto randomTileIndex = randomInt(0, randomTiles.size() - 1);
        tileToPlay = randomTiles[randomTileIndex];
        randomTiles.erase(randomTiles.begin() + randomTileIndex);
    }
    cout << endl << "> " << playerName << " has drawn the following tile:" << endl;
    cout << endl << tileToPlay << endl;
    cout << "Press [K] to rotate the tile clockwise, [L] to rotate the tile counterclockwise.\nPress [P] to place it or [D] to discard it.\nPress [Q] to quit." << endl;
    readPlayerInput(playerId, tileToPlay);
    return (playerId + 1) % playersAndScores.size();
}

void Dominos::readPlayerInput(int playerId, Tile& tileToPlay) {
    while (true) {
        string input;
        cout << endl << "> ";
        cin >> input;
        if (input == "Q") {
            announceScores(false);
        } else if (input == "K") {
            tileToPlay = tileToPlay.rotate(Rotation::CLOCKWISE);
            cout << endl << "> Here's your rotated tile:" << endl << endl << tileToPlay << endl;
        } else if (input == "L") {
            tileToPlay = tileToPlay.rotate(Rotation::COUNTERCLOCKWISE);
            cout << endl << "> Here's your rotated tile:" << endl << endl << tileToPlay << endl;
        } else if (input == "P") {
            auto attempts = 0;
            while (attempts < 3) {
                cout << "Where would you like to place it? (Enter the coordinates as x#y, (negative) whole numbers allowed) [" << 3 - attempts << " attempt(s) remaining]" << endl;
                auto option = processPlayerInput();
                if (option.isSome()) {
                    attempts--;
                    auto coords = option.unwrap();
                    if (!handlePoints(playerId, tileToPlay, coords)) {
                        if (attempts > 0) {
                            cout << "Invalid placement. Please try again." << endl;
                            attempts--;
                        } else {
                            cout << "You have reached the maximum number of attempts. The tile has been discarded." << endl;
                            return;
                        }
                    } else {
                        return;
                    }
                } else {
                    cout << "Invalid input. Please try again." << endl;
                }
            }
        } else if (input == "D") {
            cout << "> You have discarded the tile." << endl;
            return;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

bool Dominos::handlePoints(int playerId, Tile tileToPlay, pair<int, int> coords) {
    auto x = coords.first;
    auto y = coords.second;
    cout << endl << "> You have chosen to place the tile at (" << x << ", " << y << ")." << endl;
    if (board.canPlaceTile(tileToPlay, x, y)) {
        cout << "> You have successfully placed the tile!" << endl;
        board.placeTile(tileToPlay, x, y);
        // Gather neighbors to the placed tile
        auto neighbors = board.getNeighbors(x, y);
        auto pointsGained = 0;
        for (auto neighbor : neighbors) {
            for (int i = 0; i < 4; i++) {
                pointsGained += 2 * tileToPlay.getValues().at(neighbor.first)[i];
            }
        }
        cout << "> You have earned " << pointsGained << " points!" << endl;
        this->playersAndScores[playerId].second += pointsGained;
        cout << "> Your total score is " << this->playersAndScores[playerId].second << "." << endl;
        return true;
    } else {
        return false;
    }
}

Option<pair<int, int>> Dominos::processPlayerInput() {
    string input;
    cout << "> ";
    cin >> input;
    stringstream ss(input);
    string token;
    vector<string> tokens;
    while (getline(ss, token, '#')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 2) {
        return Option<pair<int, int>>();
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
    } catch (invalid_argument& e) {
        return Option<pair<int, int>>();
    }
    return Option<pair<int, int>>(make_pair(x, y));
}

void Dominos::announceScores(bool gameOver) {
    vector<pair<string, int>> sortedScores;
    for (auto score : this->playersAndScores) {
        sortedScores.push_back(score.second);
    }
    sort(sortedScores.begin(), sortedScores.end(), [](const pair<string, int>& pts1, const pair<string, int>& pts2) {
        return pts1.second > pts2.second;
    });
    if (gameOver) {
        cout << endl << "The game is over! Here are the final scores:" << endl;
        int i = 1;
        for (auto score : sortedScores) {
            cout << i << ": " << score.first << ": " << score.second << endl;
            i++;
        }
        cout << endl << "Thanks for playing! See you soon!" << endl;
        exit(0);
    } else {
        cout << endl << "The game wasn't completed. Here are the partial results:" << endl;
        int i = 1;
        for (auto score : sortedScores) {
            cout << i << ": " << score.first << ": " << score.second << endl;
            i++;
        }
        cout << endl << "Thanks for playing! See you soon!" << endl;
        exit(0);
    }
}