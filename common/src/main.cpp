#include "../include/common.hpp"
#include "../../dominos/include/dominos.hpp"

int handleQuadriminos() {
    cout << endl;
    cout << "Please enter the following information to start the game." << endl;
    cout << "You can leave a blank line to use the default value." << endl;
    int players, tilesInBag, attemptsPerTile;
    float luckFactor;
    bool satisfied = false;
    while (!satisfied) {
        try {
            cout << endl << "Number of players? ";
            string playersStr;
            getline(cin, playersStr);
            if (playersStr.empty()) {
                playersStr = "4";
            }
            players = stoi(playersStr);
            // Tiles in bag
            cout << "Number of tiles in the bag? ";
            string tilesInBagStr;
            getline(cin, tilesInBagStr);
            if (tilesInBagStr.empty()) {
                tilesInBagStr = "30";
            }
            tilesInBag = stoi(tilesInBagStr);
            // Attempts per tile
            cout << "Number of attempts to place a tile? ";
            string attemptsPerTileStr;
            getline(cin, attemptsPerTileStr);
            if (attemptsPerTileStr.empty()) {
                attemptsPerTileStr = "3";
            }
            attemptsPerTile = stoi(attemptsPerTileStr);
            // Luck factor
            cout << "Luck factor (0.0 - 1.0)? ";
            string luckFactorStr;
            getline(cin, luckFactorStr);
            if (luckFactorStr.empty()) {
                luckFactorStr = "0.05";
            }
            luckFactor = stof(luckFactorStr);
            // Confirm
            cout << endl;
            cout << "You have entered the following information:" << endl;
            cout << "Number of players: " << players << endl;
            cout << "Number of tiles in the bag: " << tilesInBag << endl;
            cout << "Number of attempts to place a tile: " << attemptsPerTile << endl;
            cout << "Luck factor: " << luckFactor << endl;
            cout << endl << "Is this correct? (Y/N) ";
            string confirm;
            getline(cin, confirm);
            if (confirm == "Y") {
                satisfied = true;
                cout << endl;
            }
        } catch (exception& e) {
            cout << "Invalid input. Please try again." << endl;
        }
    }
    Dominos dominos;
    dominos.play(1, 10, 1);
    return 0;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <1 | 2 | 3>" << endl;
        return 1;
    }
    int option = atoi(argv[1]);
    switch (option) {
        case 1: {
            cout << "You chose option 1: Quadriminos" << endl;
            handleQuadriminos();
            break;
        }
        case 2: // TODO
        case 3: // TODO
            cout << "Not implemented yet." << endl;
            return 0;
        default:
            cout << "Invalid option. Please choose 1, 2, or 3." << endl;
            return 1;
    }
    return 0;
}