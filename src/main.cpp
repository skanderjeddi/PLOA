#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/dominos.hpp"
#include "include/interface.hpp"
#include "include/game.hpp"
#include "include/trax.hpp"
#include "include/carcassonne.hpp"

int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));

    std::cout << "CARCASSONNE" << std::endl;

    sf::Font font;
    font.loadFromFile("assets/font.ttf");

    UserInterfaceProperties uiProperties;
    uiProperties.windowTitle = "Carcassonne";
    uiProperties.font = font;

    // TODO NO HARDCODED
    uiProperties.tileSize = sf::Vector2i(CARCASSONNE_TILE_SIZE, CARCASSONNE_TILE_SIZE);
    uiProperties.windowSize = sf::Vector2i(CARCASSONNE_WINDOW_WIDTH, CARCASSONNE_WINDOW_HEIGHT);
        
    BoardProperties boardProperties(CARCASSONNE_BOARD_WIDTH, CARCASSONNE_BOARD_HEIGHT);

    Carcassonne carcassonne(uiProperties, boardProperties);

    std::string line;

    auto colors = std::vector<CarcassonnePawnColor> {
        CarcassonnePawnColor::BLUE,
        CarcassonnePawnColor::RED,
        CarcassonnePawnColor::YELLOW,
        CarcassonnePawnColor::GREEN
    };

    std::cout << "Nombre de joueurs? ";
    getline(std::cin, line);
    if (line.empty()) {
        std::cout << "Nombre de joueurs par défaut: 4" << std::endl;
        line = "4";
        for (int i = 0; i < 4; i++) carcassonne.registerPlayer("Joueur " + std::to_string(i + 1), colors[i]);
    } else {
        int players = std::stoi(line);
        if (players > 4) {
            players = 4;
        }
        for (int i = 0; i < players; i++) {
            std::cout << "Joueur " << i + 1 << "? ";
            std::string name;
            getline(std::cin, name);
            carcassonne.registerPlayer(name, colors[i]);               
        }
    }

    carcassonne.run();

    return 0;
}