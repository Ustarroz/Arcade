#include <vector>
#include <string>
#include <iostream>
#include <caca.h>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "ITile.hpp"
#include "libCaca.hpp"

namespace arcade
{
  std::map<int, KeyboardKey> libCaca::m_keys
  {
    {'0', KB_0},
    {'1', KB_1},
    {'2', KB_2},
    {'3', KB_3},
    {'4', KB_4},
    {'5', KB_5},
    {'6', KB_6},
    {'7', KB_7},
    {'8', KB_8},
    {'8', KB_9},
    {276, KB_ARROW_RIGHT},
    {275, KB_ARROW_LEFT},
    {273, KB_ARROW_UP},
    {274, KB_ARROW_DOWN},
    {32, KB_SPACE},
    {13, KB_ENTER},
    {'a', KB_A},
    {'b', KB_B},
    {27, KB_ESCAPE}
  };
}
