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

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <1 | 2 | 3>" << std::endl;
        return 1;
    }
    int option = atoi(argv[1]);
    switch (option) {
        case 1: {
            std::cout << "You chose option 1: Quadriminos!" << std::endl;
            handleQuadriminos();
            break;
        }
        case 2: // TODO
        case 3: // TODO
            std::cout << "Not implemented yet." << std::endl;
            return 0;
        default:
            std::cout << "Invalid option. Please choose 1, 2, or 3." << std::endl;
            return 1;
    }
    return 0;
}