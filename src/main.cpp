#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/dominos.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"
#include "include/trax.hpp"

int main(int argc, char **argv) {
    sf::Font font;
    font.loadFromFile("assets/font.ttf");
    
    sf::Vector2i tileSize(80, 80);

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
            uiProperties.tileSize = sf::Vector2i(80, 80);
            BoardProperties boardProperties(11, 11);
            Dominos dominos(uiProperties, boardProperties);
            dominos.setTile(5, 6, DominosTile());
            dominos.run();
            break;
    }
    return 0;
}