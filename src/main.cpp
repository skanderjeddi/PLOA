#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/dominos.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));

    sf::Font font;
    font.loadFromFile("assets/font.ttf");

    UserInterfaceProperties uiProperties;
    uiProperties.font = font;

    // TODO NO HARDCODED
    
    std::cout << "1. Dominos" << std::endl;
    std::cout << "2. Trax" << std::endl;
    std::cout << "3. Carcassonne" << std::endl;
    std::cout << "> ";

    std::string choice;
    getline(std::cin, choice);
    int choiceInt = std::stoi(choice);

    switch (choiceInt) {
        case 1: {
            std::cout << "DOMINOS" << std::endl;
            
            uiProperties.windowTitle = "Dominos";
            uiProperties.tileSize = sf::Vector2i(DOMINOS_TILE_SIZE, DOMINOS_TILE_SIZE);
            uiProperties.windowSize = sf::Vector2i(DOMINOS_WINDOW_WIDTH, DOMINOS_WINDOW_HEIGHT);
        
            std::cout << "Dimensions du plateau (x#y)? ";
            std::string line;
            getline(std::cin, line);
            if (line.empty()) {
                line = "10#10";
            }
            int width = std::stoi(line.substr(0, line.find('#')));
            int height = std::stoi(line.substr(line.find('#') + 1));
            if (width > 10) {
                std::cout << "Largeur trop grande, réduite à 10" << std::endl;
                width = 10;
            }
            if (height > 10) {
                std::cout << "Longeur trop grande, réduite à 10" << std::endl;
                height = 10;
            }
            std::cout << "Largeur: " << width << ", longeur: " << height << std::endl;
            BoardProperties boardProperties(width, height);
            std::cout << "Nombre de tuiles? ";
            getline(std::cin, line);
            if (line.empty()) {
                line = "30";
            }
            int tiles = std::stoi(line);
            std::cout << "Nombre de tuiles: " << tiles << std::endl;
            Dominos dominos(uiProperties, boardProperties, tiles);
            std::cout << "Nombre de joueurs? ";
            getline(std::cin, line);
            if (line.empty()) {
                std::cout << "Nombre de joueurs par défaut: 4" << std::endl;
                line = "4";
                for (int i = 0; i < 4; i++) dominos.registerPlayer("Joueur " + std::to_string(i + 1));
            } else {
                int players = std::stoi(line);
                for (int i = 0; i < players; i++) {
                    std::cout << "Joueur " << i + 1 << "? ";
                    std::string name;
                    getline(std::cin, name);
                    dominos.registerPlayer(name);               
                }
            }
            dominos.run();
            break;
        }
        case 2: {
            uiProperties.windowTitle = "Trax";
            uiProperties.tileSize = sf::Vector2i(DOMINOS_TILE_SIZE, DOMINOS_TILE_SIZE);
            uiProperties.windowSize = sf::Vector2i(DOMINOS_WINDOW_WIDTH, DOMINOS_WINDOW_HEIGHT);
            // Configuration de la partie
                       
            Trax trax(uiProperties);
            for (int i = 0; i < 2; i++) {
                std::cout << "Joueur " << i + 1 << "? ";
                std::string name;
                getline(std::cin, name);
                trax.registerPlayer(name);               
            }
            trax.run();
            break;
        }
        case 3: {
            uiProperties.windowTitle = "Carcassonne";
            uiProperties.tileSize = sf::Vector2i(CARCASSONNE_TILE_SIZE, CARCASSONNE_TILE_SIZE);
            uiProperties.windowSize = sf::Vector2i(CARCASSONNE_WINDOW_WIDTH, CARCASSONNE_WINDOW_HEIGHT);

            BoardProperties boardProperties(CARCASSONNE_BOARD_WIDTH, CARCASSONNE_BOARD_HEIGHT);

            Carcassonne carcassonne(uiProperties, boardProperties);

            for (int i = 0; i < 4; i++) {
                std::cout << "Joueur " << i + 1 << "? ";
                std::string name;
                getline(std::cin, name);
                carcassonne.registerPlayer(name, (CarcassonnePawnColor) i);               
            }
            carcassonne.run();
        }
        default:
            break;
    }
    return 0;
}