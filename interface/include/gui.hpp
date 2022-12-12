#ifndef __GUI_HPP__
#define __GUI_HPP__

#include "../../common/include/common.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

std::map<int, Image> loadAssets();
void drawBoard(const Board&, RenderWindow&);

#endif