#include "../include/common.hpp"
#include "../../dominos/include/dominos.hpp"

int handleQuadriminos() {
    std::cout << std::endl;
    std::cout << "Please enter the following information to start the game." << std::endl;
    std::cout << "You can leave a blank line to use the default value." << std::endl;
    int players, tilesInBag, attemptsPerTile;
    float luckFactor;
    bool satisfied = false;
    while (!satisfied) {
        try {
            std::cout << std::endl << "Number of players? ";
            std::string playersStr;
            std::getline(std::cin, playersStr);
            if (playersStr.empty()) {
                playersStr = "4";
            }
            players = stoi(playersStr);
            // Tiles in bag
            std::cout << "Number of tiles in the bag? ";
            std::string tilesInBagStr;
            std::getline(std::cin, tilesInBagStr);
            if (tilesInBagStr.empty()) {
                tilesInBagStr = "30";
            }
            tilesInBag = stoi(tilesInBagStr);
            // Attempts per tile
            std::cout << "Number of attempts to place a tile? ";
            std::string attemptsPerTileStr;
            getline(std::cin, attemptsPerTileStr);
            if (attemptsPerTileStr.empty()) {
                attemptsPerTileStr = "3";
            }
            attemptsPerTile = stoi(attemptsPerTileStr);
            // Luck factor
            std::cout << "Luck factor (0.0 - 1.0)? ";
            std::string luckFactorStr;
            getline(std::cin, luckFactorStr);
            if (luckFactorStr.empty()) {
                luckFactorStr = "0.05";
            }
            luckFactor = stof(luckFactorStr);
            // Confirm
            std::cout << std::endl;
            std::cout << "You have entered the following information:" << std::endl;
            std::cout << "Number of players: " << players << std::endl;
            std::cout << "Number of tiles in the bag: " << tilesInBag << std::endl;
            std::cout << "Number of attempts to place a tile: " << attemptsPerTile << std::endl;
            std::cout << "Luck factor: " << luckFactor << std::endl;
            std::cout << std::endl << "Is this correct? (Y/N) ";
            std::string confirm;
            getline(std::cin, confirm);
            if (confirm == "Y") {
                satisfied = true;
                std::cout << std::endl;
            }
        } catch (std::exception& e) {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    Dominos dominos;
    dominos.play(players, tilesInBag, attemptsPerTile, luckFactor);
    return 0;
}

/** int main(int argc, char** argv) {
    // Check that there's no extra arguments
    if (argc > 1) {
        std::cout << "Usage: " << argv[0] << std::endl;
        return 1;
    }
    // Greet user
    std::cout << "Welcome. Please select a game to play today:" << std::endl << std::endl;
    std::cout << "\t1. Quadriminos" << std::endl;
    std::cout << "\t2. WIP" << std::endl;
    std::cout << "\t3. WIP" << std::endl;
    std::cout << "\t0. Exit" << std::endl;
    std::string choice;
    std::cout << std::endl << "Your choice? ";
    std::getline(std::cin, choice);
    try {
        int choiceInt = stoi(choice);
        switch (choiceInt) {
            case 0:
                std::cout << "Goodbye!" << std::endl;
                return 0;
            case 1:
                std::cout << "You have selected Quadriminos!" << std::endl;
                return handleQuadriminos();
            case 2:
            case 3:
                std::cout << "This game is not yet implemented." << std::endl;
                return 1;
            default:
                std::cout << "Invalid choice." << std::endl;
                return 1;
        }
    } catch (std::exception& e) {
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }
    return 0;
} **/