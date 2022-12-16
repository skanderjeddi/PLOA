#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/dominos.hpp"
#include "include/interface.hpp"

int main(int argc, char **argv) {
    DominosBoard dBoard(11, 11);
    dBoard.setTile(5, 5, DominosTile());
    sf::Font font;
    font.loadFromFile("assets/font.ttf");
    DominosInterface dInterface(dBoard, sf::Vector2i(80, 80), font);
    dInterface.run();
    return 0;
}