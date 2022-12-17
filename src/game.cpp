#include "include/game.hpp"

#include <SFML/Graphics.hpp>

#include "include/board.hpp"
#include "include/common.hpp"
#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

template <class T, class B, class I> Game<T, B, I>::Game(UserInterfaceProperties uiProperties, BoardProperties boardProperties) : interface(uiProperties, boardProperties), board(boardProperties) {
    scoreboard = std::map<int, std::pair<std::string, int>>();
}

template class Game<DominosTile, DominosBoard, DominosInterface>;
template class Game<TraxTile, TraxBoard, TraxInterface>;