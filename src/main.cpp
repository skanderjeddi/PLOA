#include "include/board.hpp"
#include "include/tile.hpp"
#include "include/dominos.hpp"

int main(int argc, char **argv) {
    std::cout << "Prout!" << std::endl;
    DominosBoard dBoard(10, 10);
    Option<DominosTile> origin = dBoard.getTile(0, 0);
    if (origin.hasValue()) {
        std::cout << "Origin: " << origin.unwrap().dataStructure().at(TileEdge::LEFT)[0] << std::endl;
    }
    return 0;
}