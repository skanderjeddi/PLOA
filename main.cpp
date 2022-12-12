#include "common.hpp"

#define NUMBER_OF_TILES 30
#define NUMBER_OF_PLAYERS 1
#define NUMBER_OF_ATTEMPTS 1

#define DEBUG true

int main(void) {
    std::cout << "Welcome to AOKD!" << std::endl;
    auto board = Board(Tile());
    std::cout << std::endl << "> Here's the initial board:" << std::endl;
    std::cout << std::endl << board << std::endl;
    std::cout << "Generating " << NUMBER_OF_TILES << " random tile(s)...    ";
    auto random_tiles = std::vector<Tile>(NUMBER_OF_TILES);
    for (int i = 0; i < NUMBER_OF_TILES; i++) {
        random_tiles[i] = Tile();
    }
    std::cout << "Done!" << std::endl;
    auto players = std::vector<std::string>(NUMBER_OF_PLAYERS);
    std::cout << std::endl << "> Enter " << NUMBER_OF_PLAYERS << " distinct name(s): " << std::endl;
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        std::cout << "Player " << i + 1 << "? ";
        std::cin >> players[i];
    }
    auto scores = std::map<std::string, int>();
    for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
        scores[players[i]] = 0;
    }
    std::cout << std::endl << "> The game will now begin!" << std::endl;
    auto current_player = (NUMBER_OF_PLAYERS <= 1) ? 0 : randomInRange(0, NUMBER_OF_PLAYERS - 1);
    bool lucky_strike = false;
    bool game_over = false;
    while (!game_over) {
        std::cout << std::endl << "> It is " << players[current_player] << "'s turn!" << std::endl;
        std::cout << "Selecting a random tile..." << std::endl;
        auto random_index = randomInRange(0, random_tiles.size() - 1);
        Tile random_tile;
        if (!lucky_strike) {
            float r = randomIn01();
            if (r > 0.1) {
                std::cout << "> Lucky strike! You get a special tile!" << std::endl;
                random_tile = board.findAppropriateTile();
                lucky_strike = true;
            }
        } else {
            lucky_strike = false;
            random_tile = random_tiles[random_index];
            random_tiles.erase(random_tiles.begin() + random_index);
        }
        std::cout << std::endl << "Here's the current board:" << std::endl;
        std::cout << std::endl << board;
        std::cout << std::endl << "> " << players[current_player] << " has drawn the following tile:" << std::endl;
        std::cout << std::endl << random_tile << std::endl;
        std::cout << std::endl << "[" << random_tiles.size() << " remaining tiles]" << std::endl;
        std::cout << std::endl << "Press [K] to rotate the tile clockwise, [L] to rotate the tile counterclockwise.\nPress [P] to place it or [D] to discard it.\nPress [Q] to quit." << std::endl;
        auto discarded = false;
        auto read_input = true;
        auto attempts = NUMBER_OF_ATTEMPTS;
        while (read_input) {
            std::string input;
            std::cout << std::endl << "> ";
            std::cin >> input;
            if (input == "Q") {
                std::cout << std::endl << "Thanks for playing! See you next time!" << std::endl;
                return 0;
            } else if (input == "K") {
                random_tile = random_tile.rotate(Rotation::CLOCKWISE);
                std::cout << std::endl << "> Here's your rotated tile:" << std::endl << std::endl << random_tile << std::endl;
            } else if (input == "L") {
                random_tile = random_tile.rotate(Rotation::COUNTERCLOCKWISE);
                std::cout << std::endl << "> Here's your rotated tile:" << std::endl << std::endl << random_tile << std::endl;
            } else if (input == "P") {
                while (attempts > 0) {
                    std::cout << "Where would you like to place it? (Enter the coordinates as x#y, (negative) whole numbers allowed) [" << attempts << " possible attempt(s)]" << std::endl;
                    std::string input;
                    std::cout << "> ";
                    std::cin >> input;
                    std::stringstream ss(input);
                    std::string token;
                    std::vector<std::string> tokens;
                    while (std::getline(ss, token, '#')) {
                        tokens.push_back(token);
                    }
                    if (tokens.size() != 2) {
                        std::cout << "Invalid input. Please try again." << std::endl;
                        continue;
                    }
                    int x, y;
                    bool negative_x = false, negative_y = false;
                    if (tokens[0].at(0) == '-') {
                        negative_x = true;
                        tokens[0] = tokens[0].substr(1);
                    }
                    if (tokens[1].at(0) == '-') {
                        negative_y = true;
                        tokens[1] = tokens[1].substr(1);
                    }
                    try {
                        x = std::stoi(tokens[0]) * (negative_x ? -1 : 1);
                        y = std::stoi(tokens[1]) * (negative_y ? -1 : 1);
                    } catch (std::invalid_argument& e) {
                        std::cout << "Invalid input. Please try again." << std::endl;
                        continue;
                    }
                    std::cout << std::endl << "> You have chosen to place the tile at (" << x << ", " << y << ")." << std::endl;
                    std::cout << board.canPlaceTile(random_tile, x, y) << std::endl;
                    attempts--;
                    if (board.canPlaceTile(random_tile, x, y)) {
                        std::cout << "> You have successfully placed the tile!" << std::endl;
                        board.placeTile(random_tile, x, y);
                        // Gather neighbors to the placed tile
                        auto neighbours = board.getNeighbors(x, y);
                        auto points_gained = 0;
                        for (auto neighbour : neighbours) {
                            for (int i = 0; i < 4; i++) {
                                points_gained += 2 * random_tile.getValues().at(neighbour.first)[i];
                            }
                        }
                        std::cout << "> You have earned " << points_gained << " points!" << std::endl;
                        scores[players[current_player]] += points_gained;
                        std::cout << "> Your total score is " << scores[players[current_player]] << "." << std::endl;
                        current_player = (current_player + 1) % NUMBER_OF_PLAYERS;
                        read_input = false;
                        break;
                    } else {
                        if (attempts > 0) {
                            std::cout << "Invalid placement. Please try again." << std::endl;
                            attempts--;
                        } else {
                            std::cout << "You have reached the maximum number of attempts. The tile has been discarded." << std::endl;
                            read_input = false;
                            break;
                        }
                    }
                }
            } else if (input == "D") {
                std::cout << "> You have discarded the tile." << std::endl;
                current_player = (current_player + 1) % NUMBER_OF_PLAYERS;
                discarded = true && !lucky_strike;
                break;
            } else {
                std::cout << "Invalid input. Please try again." << std::endl;
            }
        }
        if (discarded) {
            if (random_tiles.size() == 0) {
                std::cout << std::endl << "> There are no more tiles left. The game is over!" << std::endl;
                game_over = true;
                break;
            } else {
                continue;
            }
        }
    }
    // Announce that the game is over and display the final scores sorted by highest to lowest
    std::cout << std::endl << "The game is over! Here are the final scores:" << std::endl;
    std::vector<std::pair<std::string, int>> sorted_scores;
    for (auto score : scores) {
        sorted_scores.push_back(score);
    }
    std::sort(sorted_scores.begin(), sorted_scores.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });
    for (auto score : sorted_scores) {
        std::cout << score.first << ": " << score.second << std::endl;
    }
    std::cout << std::endl << "Thanks for playing! See you soon!" << std::endl;
    return 0;
}