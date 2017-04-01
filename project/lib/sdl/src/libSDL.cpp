#include <vector>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "libSDL.hpp"

namespace arcade
{
  libSDL::libSDL()
    : m_doesSupportSound(true), m_windowHeight(640), m_windowWeight(640)
  {
    initSDL();
  }

  libSDL::libSDL(int height, int weight)
    : m_doesSupportSound(true), m_windowHeight(height), m_windowWeight(weight)
  {
    initSDL();
  }

  libSDL::~libSDL()
  {
    SDL_DestroyWindow(m_disp.window);
    SDL_Quit();
  }

  int libSDL::initSDL()
  {
    SDL_Init(SDL_INIT_VIDEO);
    m_disp.window = SDL_CreateWindow("Arcade - SDL", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, m_windowWeight,
                                m_windowHeight, SDL_WINDOW_SHOWN);
    if (m_disp.window == NULL)
    {
      std::cerr << SDL_GetError() << std::endl;
      return (1);
    }
    m_disp.screen = SDL_GetWindowSurface(m_disp.window);
    m_disp.palette = SDL_AllocPalette(10);
    setPalette(m_disp.palette);
    return (0);
  }

  bool libSDL::pollEvent(Event &e)
  {
    return (false);
  }

  bool libSDL::doesSupportSound() const
  {
    return (m_doesSupportSound);
  }

  void libSDL::loadSounds(std::vector<std::string> const &sound)
  {
  }

  void libSDL::soundControl(const Sound &sound)
  {
    std::cout << "PLAYSOUND func" << std::endl;
  }

  void libSDL::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
  }

  void libSDL::updateMap(IMap const &map)
  {
  }

  void libSDL::updateGUI(IGUI &gui)
  {
    pos_t pos;
    SDL_memset(m_disp.screen->pixels, 0,
        m_disp.screen->h * m_disp.screen->pitch);
    pos.x = 100;
    pos.y = 100;
    drawSquare(m_disp.screen, pos, 50, &m_disp.palette->colors[0]);
  }

  void libSDL::display()
  {
    std::cout << "DISPLAY func" << std::endl;
    SDL_UpdateWindowSurface(m_disp.window);
    SDL_Delay(600);
  }

  void libSDL::clear()
  {
    std::cout << "CLEAR func" << std::endl;
  }

  void libSDL::setPalette(SDL_Palette *pal)
  {
    SDL_Color	colors[10] =
    {{26, 188, 156, 255},
      {46, 204, 113, 255},
      {52, 152, 219, 255},
      {155, 89, 182, 255},
      {236, 240, 241, 255},
      {241, 196, 15, 255},
      {230, 126, 34, 255},
      {231, 76, 60, 255},
      {232, 12, 184, 255},
      {29, 255, 238, 255}};

    SDL_SetPaletteColors(pal, colors, 0, 10);
  }

  void libSDL::drawSquare(SDL_Surface *surface, pos_t pos, int size, SDL_Color *color)
  {
    for (int y = pos.y; y < pos.y + size; y++)
    {
      for (int x = pos.x; x < pos.x + size; x++)
      {
        drawPixel(surface, {x, y}, color);
      }
    }
  }

  void libSDL::drawPixel(SDL_Surface *surface, pos_t pos, SDL_Color *color)
  {
    SDL_Color *pixel;

    pixel = static_cast<SDL_Color *>(surface->pixels) + pos.x + pos.y * m_windowWeight;
    pixel->r = color->r;
    pixel->g = color->g;
    pixel->b = color->b;
    pixel->a = color->a;
  }
}

extern "C"
{
  arcade::IGfxLib *entryPoint()
  {
    return (new arcade::libSDL());
  }
}
