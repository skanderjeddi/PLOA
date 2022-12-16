#include "include/game.hpp"

#include <SFML/Graphics.hpp>

#include "include/board.hpp"
#include "include/common.hpp"
#include "include/dominos.hpp"
#include "include/trax.hpp"
#include "include/tile.hpp"
#include "include/interface.hpp"

template <class I> Game<I>::Game(const sf::Vector2i& tileSize, const sf::Font& font) : tileSize(tileSize), font(font) {
    scoreboard = std::map<int, std::pair<std::string, int>>();
    configure();
    run();
}

template class Game<DominosInterface>;
template class Game<TraxInterface>;