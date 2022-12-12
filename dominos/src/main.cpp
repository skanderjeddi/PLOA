#include "include/common.hpp"

#define NUMBER_OF_TILES 10
#define NUMBER_OF_PLAYERS 1
#define NUMBER_OF_ATTEMPTS 3
#define LUCKY_EPSILON 0.09

#define DEBUG true

using namespace std;

int main(void) {
    cout << "Welcome to AOKD!" << endl;
    auto initialTile = Tile();
    auto board = Board(initialTile, make_pair(0, 0));
    cout << endl << "> Here's the initial board:" << endl;
    cout << endl << board << endl;
    cout << "Generating " << NUMBER_OF_TILES << " random tile(s)...    ";
    auto randomTiles = board.generateRandomTiles(NUMBER_OF_TILES);
    cout << "Done!" << endl;
    auto players = vector<string>(NUMBER_OF_PLAYERS);
    cout << endl << "> Enter " << NUMBER_OF_PLAYERS << " distinct name(s): " << endl;
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        cout << "Player " << i + 1 << "? ";
        cin >> players[i];
    }
    auto scores = map<string, int>();
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        scores[players[i]] = 0;
    }
    cout << endl << "> The game will now begin!" << endl;
    auto currentPlayer = (NUMBER_OF_PLAYERS <= 1) ? 0 : randomInt(0, NUMBER_OF_PLAYERS - 1);
    bool luckyStrike = false;
    bool gameOver = false;
    while (!gameOver) {
        cout << endl << "> It is " << players[currentPlayer] << "'s turn!" << endl;
        cout << "Here's the current board:" << endl;
        cout << endl << board;
        cout << endl << "Selecting a random tile..." << endl;
        auto randomTileIndex = randomInt(0, randomTiles.size() - 1);
        Tile tileToPlay;
        if (!luckyStrike) {
            float r = randomFloat();
            if (r < static_cast<float>(LUCKY_EPSILON)) {
                cout << endl << "-------------------------------------" << endl;
                cout << "Lucky strike! You get a special tile!" << endl;
                cout << "-------------------------------------" << endl;
                tileToPlay = board.findTileThatFits();
                luckyStrike = true;
            }
        } else {
            luckyStrike = false;
            tileToPlay = randomTiles[randomTileIndex];
            randomTiles.erase(randomTiles.begin() + randomTileIndex);
        }
        cout << endl << "> " << players[currentPlayer] << " has drawn the following tile:" << endl;
        cout << endl << tileToPlay << endl;
        cout << endl << "[" << randomTiles.size() << " remaining tiles]" << endl;
        cout << endl << "Press [K] to rotate the tile clockwise, [L] to rotate the tile counterclockwise.\nPress [P] to place it or [D] to discard it.\nPress [Q] to quit." << endl;
        auto tileWasDiscarded = false;
        auto readInput = true;
        auto attempts = NUMBER_OF_ATTEMPTS;
        while (readInput) {
            string input;
            cout << endl << "> ";
            cin >> input;
            if (input == "Q") {
                cout << endl << "Thanks for playing! See you next time!" << endl;
                return 0;
            } else if (input == "K") {
                tileToPlay = tileToPlay.rotate(Rotation::CLOCKWISE);
                cout << endl << "> Here's your rotated tile:" << endl << endl << tileToPlay << endl;
            } else if (input == "L") {
                tileToPlay = tileToPlay.rotate(Rotation::COUNTERCLOCKWISE);
                cout << endl << "> Here's your rotated tile:" << endl << endl << tileToPlay << endl;
            } else if (input == "P") {
                while (attempts > 0) {
                    cout << "Where would you like to place it? (Enter the coordinates as x#y, (negative) whole numbers allowed) [" << attempts << " possible attempt(s)]" << endl;
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
                        cout << "Invalid input. Please try again." << endl;
                        continue;
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
                        cout << "Invalid input. Please try again." << endl;
                        continue;
                    }
                    cout << endl << "> You have chosen to place the tile at (" << x << ", " << y << ")." << endl;
                    cout << board.canPlaceTile(tileToPlay, x, y) << endl;
                    attempts--;
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
                        scores[players[currentPlayer]] += pointsGained;
                        cout << "> Your total score is " << scores[players[currentPlayer]] << "." << endl;
                        currentPlayer = (currentPlayer + 1) % NUMBER_OF_PLAYERS;
                        readInput = false;
                        break;
                    } else {
                        if (attempts > 0) {
                            cout << "Invalid placement. Please try again." << endl;
                            attempts--;
                        } else {
                            cout << "You have reached the maximum number of attempts. The tile has been discarded." << endl;
                            readInput = false;
                            break;
                        }
                    }
                }
            } else if (input == "D") {
                cout << "> You have discarded the tile." << endl;
                currentPlayer = (currentPlayer + 1) % NUMBER_OF_PLAYERS;
                tileWasDiscarded = true && !luckyStrike;
                break;
            } else {
                cout << "Invalid input. Please try again." << endl;
            }
        }
        if (tileWasDiscarded) {
            if (randomTiles.size() == 0) {
                cout << endl << "> There are no more tiles left. The game is over!" << endl;
                gameOver = true;
                break;
            } else {
                continue;
            }
        }
    }
    // Announce that the game is over and display the final scores sorted by highest to lowest
    cout << endl << "The game is over! Here are the final scores:" << endl;
    vector<pair<string, int>> sortedScores;
    for (auto score : scores) {
        sortedScores.push_back(score);
    }
    sort(sortedScores.begin(), sortedScores.end(), [](const pair<string, int>& pts1, const pair<string, int>& pts2) {
        return pts1.second > pts2.second;
    });
    for (auto score : sortedScores) {
        cout << score.first << ": " << score.second << endl;
    }
    cout << endl << "Thanks for playing! See you soon!" << endl;
    return 0;
}