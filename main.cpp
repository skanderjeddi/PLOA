#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"

int main(void) {
    Tile initial;
    Board board(initial);
    board.place_tile(Tile(), -1, -1);
    board.place_tile(Tile(), 0, 1);
    board.place_tile(Tile(), 0, 4);
    board.place_tile(Tile(), 1, 0);
    board.place_tile(Tile(), 1, 2);
    board.place_tile(Tile(), 1, 1);
    std::cout << board << std::endl;
    /**Tile candidate;
    while (!board.can_place_tile(candidate, 0, 1)) {
        candidate = Tile();
    }
    std::cout << "Candidate tile: " << std::endl << candidate << "can be placed right below the initial tile." << std::endl;**/
    return 0;
}