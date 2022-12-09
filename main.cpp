#include "common.hpp"
#include "tile.hpp"
#include "board.hpp"

int main(void) {
    Tile initial;
    Board board(initial);
    board.place_tile(Tile(), 1, 0);
    board.place_tile(Tile(), 2, 0);
    board.place_tile(Tile(), 0, 1);
    board.place_tile(Tile(), 1, 1);
    board.place_tile(Tile(), 3, 1);
    board.place_tile(Tile(), 1, 2); 
    // board.place_tile(Tile(), 3, 2);
    std::cout << board;
    // board.place_tile(Tile(), 4, 3);
    // board.place_tile(Tile(), 2, 3);
    Tile candidate = Tile();
    bool keep_going = true;
    while (keep_going) {
        for (int i = 0; i < 4; i++) {
            if (board.can_place_tile(candidate, 3, 3)) {
                keep_going = false;
            } else {
                candidate.rotate();
            }
        }
        if (!keep_going) {
            break;
        }
        candidate = Tile();
    }
    // std::cout << candidate << std::endl;
    return 0;
}