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

    UserInterfaceProperties uiProperties;
    uiProperties.font = font;
    uiProperties.tileSize = sf::Vector2i(DOMINOS_TILE_SIZE, DOMINOS_TILE_SIZE);
    uiProperties.windowSize = sf::Vector2i(DOMINOS_WINDOW_WIDTH, DOMINOS_WINDOW_HEIGHT);
    BoardProperties boardProperties(6, 6);
    Dominos dominos(uiProperties, boardProperties);
    dominos.registerPlayer("Skander");
    dominos.registerPlayer("Florent");
    dominos.registerPlayer("Margot");
    dominos.run();
    return 0;
}