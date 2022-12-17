#include "include/game.hpp"

#include <SFML/Graphics.hpp>

#include "include/board.hpp"
#include "include/common.hpp"
#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

template <class B, class I> Game<B, I>::Game(UserInterfaceProperties uiProperties, BoardProperties boardProperties) : _interface(uiProperties, boardProperties), _board(boardProperties) {
    scoreboard = std::map<int, std::pair<std::string, int>>();
}

template class Game<DominosBoard, DominosInterface>;
template class Game<TraxBoard, TraxInterface>;