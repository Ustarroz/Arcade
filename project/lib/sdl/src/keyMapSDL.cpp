#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "ITile.hpp"
#include "libSDL.hpp"

namespace arcade
{
  std::map<SDL_Keycode, KeyboardKey> libSDL::m_keys =
    {
    {SDLK_0, KB_0},
    {SDLK_1, KB_1},
    {SDLK_2, KB_2},
    {SDLK_3, KB_3},
    {SDLK_4, KB_4},
    {SDLK_5, KB_5},
    {SDLK_6, KB_6},
    {SDLK_7, KB_7},
    {SDLK_8, KB_8},
    {SDLK_9, KB_9},
    {SDLK_RIGHT, KB_ARROW_RIGHT},
    {SDLK_LEFT, KB_ARROW_LEFT},
    {SDLK_UP, KB_ARROW_UP},
    {SDLK_DOWN, KB_ARROW_DOWN},
    {SDLK_SPACE, KB_SPACE},
    {SDLK_RETURN, KB_ENTER},
    {SDLK_a, KB_A},
    {SDLK_b, KB_B},
    {224, KB_0},
    {SDLK_AMPERSAND, KB_1},
    {233, KB_2},
    {34, KB_3},
    {39, KB_4},
    {40, KB_5},
    {45, KB_6},
    {232, KB_7},
    {95, KB_8},
    {231, KB_9},
    {SDLK_ESCAPE, KB_ESCAPE}
    };
}
