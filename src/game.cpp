#include "include/game.hpp"

#include <SFML/Graphics.hpp>

#include "include/board.hpp"
#include "include/common.hpp"
#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"
#include "include/carcassonne.hpp"

template <class T, class B, class I> Game<T, B, I>::Game(UserInterfaceProperties uiProperties, BoardProperties boardProperties) : board(boardProperties), interface(uiProperties, boardProperties)  {
    scoreboard = std::map<int, std::pair<std::string, int>>();
}

template class Game<DominosTile, DominosBoard, DominosInterface>;
template class Game<TraxTile, TraxBoard, TraxInterface>;
template class Game<CarcassonneTile, CarcassonneBoard, CarcassonneInterface>;