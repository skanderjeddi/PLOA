#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/dominos.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"
#include "include/trax.hpp"

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));

    sf::Font font;
    font.loadFromFile("assets/font.ttf");
    
    std::cout << "1. Dominos" << std::endl;
    std::cout << "2. Trax" << std::endl;
    std::cout << "3. Carcassonne (WIP)" << std::endl;
    std::cout << "> ";

    std::string choice;
    getline(std::cin, choice);
    int choiceInt = std::stoi(choice);

    switch (choiceInt) {
        case 1:
            UserInterfaceProperties uiProperties;
            uiProperties.font = font;
            uiProperties.tileSize = sf::Vector2i(DOMINOS_TILE_SIZE, DOMINOS_TILE_SIZE);
            uiProperties.windowSize = sf::Vector2i(DOMINOS_WINDOW_WIDTH, DOMINOS_WINDOW_HEIGHT);
            // Configuration de la partie
            std::cout << "Dimensions du plateau (x-y)? ";
            std::string line;
            getline(std::cin, line);
            int width = std::stoi(line.substr(0, line.find('-')));
            int height = std::stoi(line.substr(line.find('-') + 1));
            std::cout << "Largeur: " << width << ", longeur: " << height << std::endl;
            BoardProperties boardProperties(width, height);
            Dominos dominos(uiProperties, boardProperties);
            std::cout << "Nombre de joueurs? ";
            getline(std::cin, line);
            int players = std::stoi(line);
            for (int i = 0; i < players; i++) {
                std::cout << "Joueur " << i + 1 << "? ";
                std::string name;
                getline(std::cin, name);
                dominos.registerPlayer(name);               
            }
            dominos.run();
            break;
    }
    return 0;
}