#include "include/dominos.hpp"

int handleDominos() {
    std::cout << std::endl;
    std::cout << "Please enter the following information to start the game." << std::endl;
    std::cout << "You can leave a blank line to use the (default value)." << std::endl;
    int players, tilesInBag, rows, columns;;
    bool satisfied = false;
    while (!satisfied) {
        try {
            std::cout << std::endl << "Number of players (4)? ";
            std::string playersStr;
            std::getline(std::cin, playersStr);
            if (playersStr.empty()) {
                playersStr = "4";
            }
            players = stoi(playersStr);
            // Number of columns
            std::cout << "Number of columns (11)? ";
            std::string columnsStr;
            std::getline(std::cin, columnsStr);
            if (columnsStr.empty()) {
                columnsStr = "11";
            }
            columns = stoi(columnsStr);
            // Number of rows
            std::cout << "Number of rows (9)? ";
            std::string rowsStr;
            std::getline(std::cin, rowsStr);
            if (rowsStr.empty()) {
                rowsStr = "9";
            }
            rows = stoi(rowsStr);
            // Tiles in bag
            std::cout << "Number of tiles in the bag (30)? ";
            std::string tilesInBagStr;
            std::getline(std::cin, tilesInBagStr);
            if (tilesInBagStr.empty()) {
                tilesInBagStr = "30";
            }
            tilesInBag = stoi(tilesInBagStr);
            // Confirm
            std::cout << std::endl;
            std::cout << "You have entered the following information:" << std::endl;
            std::cout << "Number of players: " << players << std::endl;
            std::cout << "Number of columns: " << columns << std::endl;
            std::cout << "Number of rows: " << rows << std::endl;
            std::cout << "Number of tiles in the bag: " << tilesInBag << std::endl;
            std::cout << std::endl << "Is this correct? (Y/N) ";
            std::string confirm;
            getline(std::cin, confirm);
            if (confirm == "Y" || confirm.empty()) {
                satisfied = true;
                std::cout << std::endl;
            }
        } catch (std::exception& e) {
            std::cout << "Invalid input. Please try again." << std::endl;
        }
    }
    Dominos dominos(std::make_pair(columns, rows), tilesInBag);
    dominos.play(std::make_pair(90, 90), players);
    return 0;
}

int main(int argc, char** argv) {
    // Check that there's no extra arguments
    if (argc > 1) {
        std::cout << "Usage: " << argv[0] << std::endl;
        return 1;
    }
    // Greet user
    std::cout << "Welcome! Please select a game to play today:" << std::endl;
    std::cout << "\t1. Dominos" << std::endl;
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
                return handleDominos();
            /** case 2:
            case 3:
                std::cout << "This game is not yet implemented." << std::endl;
                return 1; **/
            default:
                std::cout << "Invalid choice." << std::endl;
                return 1;
        }
    } catch (std::exception& e) {
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }
    return 0;
}
