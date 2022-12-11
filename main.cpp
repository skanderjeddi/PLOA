#include "common.hpp"

std::string tiles_to_terminal(std::map<int, std::map<int, Tile>> sorted, std::pair<int, int> mins, std::pair<int, int> maxs, int y, int k) {
    auto line = std::string();
    auto linesWithY = sorted[y];
    // print all y values
    for (int x = 0; x <= mins.first + maxs.first; x++) {
        if (linesWithY.find(x) != linesWithY.end()) {
            line += linesWithY[x].line_representation(k) + "\t";
        } else {
            line += "        ";
        }
    }
    return line;
}

int main(void) {
    std::cout << "Thanks for playing the game!" << std::endl;
    auto board = Board(Tile());
    std::cout << std::endl << "Initial tile:" << std::endl;
    std::cout << board << std::endl;
    std::cout << "Generating 30 random tiles...    ";
    auto random_tiles = std::vector<Tile>(30);
    for (int i = 0; i < 30; i++) {
        random_tiles[i] = Tile();
    }
    std::cout << "Done!" << std::endl;
    auto players = std::vector<std::string>(4);
    std::cout << std::endl << "Enter 4 distinct names: " << std::endl;
    for (int i = 0; i < 4; i++) {
        std::cout << "Player " << i + 1 << ": ";
        std::cin >> players[i];
    }
    auto scores = std::map<std::string, int>();
    for (int i = 0; i < 4; i++) {
        scores[players[i]] = 0;
    }
    std::cout << std::endl << "The game will now begin!" << std::endl;
    auto current_player = random_in_range(0, 3);
    while (true) {
        std::cout << "It is " << players[current_player] << "'s turn!" << std::endl;
        std::cout << "Selecting a random tile..." << std::endl;
        auto random_index = random_in_range(0, random_tiles.size() - 1);
        auto random_tile = random_tiles[random_index];
        std::cout << std::endl << players[current_player] << " has drawn the following tile:" << std::endl;
        std::cout << random_tile << std::endl;
        std::cout << std::endl << "Press R0 to rotate the tile clockwise, R1 to rotate the tile counterclockwise. Press P to place it or D to discard it." << std::endl;
        std::cout << std::endl << "(Press B to display the board.)" << std::endl;
        auto discarded = false;
        while (true) {
            std::string input;
            std::cin >> input;
            if (input == "R0") {
                random_tile = random_tile.rotate(Rotation::CLOCKWISE);
                std::cout << "Here's your rotated tile:" << std::endl << random_tile << std::endl;
            } else if (input == "R1") {
                random_tile = random_tile.rotate(Rotation::COUNTERCLOCKWISE);
                std::cout << "Here's your rotated tile:" << std::endl << random_tile << std::endl;
            } else if (input == "P") {
                break;
            } else if (input == "D") {
                std::cout << "You have discarded the tile." << std::endl;
                random_tiles.erase(random_tiles.begin() + random_index);
                current_player = (current_player + 1) % 4;
                discarded = true;
                break;
            } else if (input == "B") {
                std::cout << board << std::endl;
            } else {
                std::cout << "Invalid input. Please try again." << std::endl;
            }
        }
        if (discarded) {
            continue;
        }
        auto attempts = 1;
        auto success = false;
        while (attempts <= 3) {
            std::cout << "Where would you like to place it? (Enter the coordinates as x#y, negative whole numbers allowed)" << std::endl;
            std::cout << "[" << (3 - attempts) << " attempts remaining]" << std::endl;
            std::string input;
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
            try {
                x = std::stoi(tokens[0]);
                y = std::stoi(tokens[1]);
            } catch (std::invalid_argument& e) {
                std::cout << "Invalid input. Please try again." << std::endl;
                continue;
            }
            if (board.can_place_tile(random_tile, x, y)) {
                std::cout << "You have successfully placed the tile!" << std::endl;
                board.place_tile(random_tile, x, y);
                // Gather neighbors to the placed tile
                auto neighbours = board.get_neighbours(x, y);
                auto points_gained = 0;
                for (auto neighbour : neighbours) {
                    for (int i = 0; i < 4; i++) {
                        points_gained += 2 * random_tile.get_values().at(neighbour.first)[i];
                    }
                }
                std::cout << "You have gained " << points_gained << " points." << std::endl;
                scores[players[current_player]] += points_gained;
                std::cout << "Your total score is " << scores[players[current_player]] << std::endl;
                random_tiles.erase(random_tiles.begin() + random_index);
                current_player = (current_player + 1) % 4;
                success = true;
                break;
            } else {
                std::cout << "Invalid placement. Please try again." << std::endl;
                attempts++;
            }
            if (success) {
                break;
            }
        }
    }
    return 0;
}