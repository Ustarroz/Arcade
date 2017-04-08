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
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type){
        case SDL_KEYDOWN:
#ifdef DEBUG
          std::cout << "Key combination: " << event.key.keysym.sym << std::endl;
#endif
          for (std::map<SDL_Keycode, KeyboardKey>::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
          {
            if (event.key.keysym.sym == it->first)
            {
              if (it->first == SDLK_ESCAPE)
                return (false);
              e.type = ET_KEYBOARD;
              e.action = AT_PRESSED;
              e.kb_key = it->second;
            }
          }
      }
    }
    return (true);
  }

  bool libSDL::doesSupportSound() const
  {
    //return (m_doesSupportSound);
    return (false);
  }

  void libSDL::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sound)
  {
#ifdef DEBUG
    std::cout << "[SDL] LOAD SOUNDS" << std::endl;
#endif
  }

  void libSDL::soundControl(const Sound &sound)
  {
#ifdef DEBUG
    std::cout << "[SDL] SOUND CONTROL" << std::endl;
#endif
  }

  void libSDL::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
#ifdef DEBUG
    std::cout << "[SDL] LOAD SPRITES" << std::endl;
#endif
  }

  void libSDL::updateMap(IMap const &map)
  {
    for (size_t nb = 0; nb < map.getLayerNb(); nb++)
    {
      for (size_t y = 0; y < map.getHeight(); y++)
      {
        for (size_t x = 0; x < map.getWidth(); x++)
        {
          ITile const &tile = map.at(nb, x, y);
          Color a = tile.getColor();
          SDL_Color color = {a.r, a.g, a.b, a.a};
          pos_t pos = {static_cast<int>(x * 10), static_cast<int>(y * 10)};
          drawSquare(m_disp.screen, pos, 10, &color);
        }
      }
    }
  }

  void libSDL::updateGUI(IGUI &gui)
  {
    for (size_t nb = 0; nb < gui.size(); nb++)
    {
      IComponent &c = gui.at(nb);
      SDL_Color red = {255, 0, 0, 255};
      pos_t pos = {static_cast<int>(static_cast<double>(m_windowWeight) * c.getX()), static_cast<int>(static_cast<double>(m_windowHeight) * c.getY())};
      drawRect(m_disp.screen, pos, c.getWidth(), c.getHeight(), &red);
#ifdef DEBUG
      std::cout << c.getText() << std::endl;
#endif
    }
  }

  void libSDL::display()
  {
    SDL_UpdateWindowSurface(m_disp.window);
  }

  void libSDL::clear()
  {
    SDL_memset(m_disp.screen->pixels, 0,
        m_disp.screen->h * m_disp.screen->pitch);
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

  void libSDL::drawRect(SDL_Surface *surface, pos_t pos, int size_x, int size_y, SDL_Color *color)
  {
    for (int y = pos.y; y < pos.y + size_y; y++)
    {
      for (int x = pos.x; x < pos.x + size_x; x++)
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
  arcade::IGfxLib *getLib()
  {
    return (new arcade::libSDL());
  }
}
