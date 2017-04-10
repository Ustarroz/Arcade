#include <vector>
#include <string>
#include <iostream>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "libLapin.hpp"
#include "Common.hpp"
#include "ITile.hpp"
#include "lapin.h"

namespace arcade
{
  libLapin::libLapin()
    : m_doesSupportSound(true), m_windowHeight(640), m_windowWeight(640), m_map(NULL), m_gui(NULL)
  {
    initLapin();
  }

  libLapin::libLapin(int height, int weight)
    : m_doesSupportSound(true), m_windowHeight(height), m_windowWeight(weight), m_map(NULL), m_gui(NULL)
  {
    initLapin();
  }

  libLapin::~libLapin()
  {
    bunny_stop(m_prog.win);
  }

  int libLapin::initLapin()
  {
    m_prog.win = bunny_start(m_windowWeight, m_windowHeight, false, "Arcade - Lapin");
    if (m_prog.win == NULL)
    {
      bunny_printlerr("Cannot open the window.");
      return (1);
    }
    m_prog.name = "Arcade";
    m_render = bunny_new_pixelarray(m_windowWeight, m_windowHeight);
    bunny_clear(&m_prog.win->buffer, PINK2);
    //bunny_printl("Press escape to exit. Click left to change the window color.");
    //bunny_set_key_response(key_response);
    //bunny_set_click_response(click_response);
    //bunny_set_loop_main_function(libLap_bunnyMainLoop);
    //bunny_loop(m_prog.win, 25, &m_prog);
    display();
#ifdef DEBUG
    std::cout << "[Lapin] init ok" << std::endl;
#endif
  }

  bool libLapin::pollEvent(Event &e)
  {
    return (false);
  }

  bool libLapin::doesSupportSound() const
  {
    return (false);
  }

  void libLapin::loadSounds(std::vector<std::pair<std::string, SoundType > > const &sounds)
  {
    (void)sounds;
  }

  void libLapin::soundControl(const Sound &sound)
  {
    (void)sound;
  }

  void libLapin::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    (void)sprites;
  }

  void libLapin::updateMap(IMap const &map)
  {
#ifdef DEBUG
    std::cout << "[Lapin] updating map" << std::endl;
#endif
    m_map = &map;
    bunny_set_loop_main_function(libLapin::_bunnyUpdateMap);
    bunny_loop(m_prog.win, 60, this);
  }

  void libLapin::updateGUI(IGUI &gui)
  {
#ifdef DEBUG
    std::cout << "[Lapin] updating GUI" << std::endl;
#endif
    m_gui = &gui;
    bunny_set_loop_main_function(&_bunnyUpdateGUI);
    bunny_loop(m_prog.win, 60, this);
  }

  void libLapin::display()
  {
    bunny_set_loop_main_function(&_bunnyDisplay);
    bunny_loop(m_prog.win, 60, this);
  }

  void libLapin::clear()
  {
    bunny_set_loop_main_function(&_bunnyClear);
    bunny_loop(m_prog.win, 60, this);
  }

  t_bunny_response libLapin::_bunnyUpdateMap(void *data)
  {
    libLapin *lapin = static_cast<libLapin *>(data);
    if (lapin->m_map == NULL)
      return (EXIT_ON_SUCCESS);
    for (size_t nb = 0; nb < lapin->m_map->getLayerNb(); nb++)
    {
      for (size_t y = 0; y < lapin->m_map->getHeight(); y++)
      {
        for (size_t x = 0; x < lapin->m_map->getWidth(); x++)
        {
          ITile const &tile = lapin->m_map->at(nb, x, y);
          pos_t pos = {static_cast<int>(x * SIZE_TILE), static_cast<int>(y * SIZE_TILE)};
          Color col = tile.getColor();
          lapin->drawSquare(lapin, pos, SIZE_TILE, col);
          /*if (tile.hasSprite() && m_sprites.size() > 0)
          {
            //disp sprite     
          }
          else
          {
            //disp simple rect
          }*/
        }
      }
    }
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response libLapin::_bunnyUpdateGUI(void *data)
  {
    libLapin *lapin = static_cast<libLapin *>(data);
    if (lapin->m_gui == NULL)
      exit(EXIT_ON_SUCCESS);
    for (size_t nb = 0; nb < lapin->m_gui->size(); nb++)
    {
      IComponent const &c = lapin->m_gui->at(nb);
      pos_t pos = {static_cast<int>(static_cast<double>(lapin->m_windowWeight) * c.getX()), static_cast<int>(static_cast<double>(lapin->m_windowHeight) * c.getY())};
      //drawRect(m_disp.screen, pos, c.getWidth(), c.getHeight(), &red);
#ifdef DEBUG
      //std::cout << c.getText() << std::endl;
#endif
      //if (m_font)
      //{
        //font ok so disp c.getText().c_str();
      //}
      /*else
      {
#ifdef DEBUG
        std::cout << "Cannot load font : " << TTF_GetError() << std::endl;
#endif
      }*/
    }
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response libLapin::_bunnyDisplay(void *data)
  {
    libLapin *lapin = static_cast<libLapin *>(data);
    bunny_blit(&lapin->m_prog.win->buffer, &lapin->m_render->clipable, NULL);
    bunny_display(lapin->m_prog.win);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response libLapin::_bunnyClear(void *data)
  {
    libLapin *lapin = static_cast<libLapin *>(data);
    //bunny_display(m_prog->win);
    return (EXIT_ON_SUCCESS);
  }

  void libLapin::drawSquare(libLapin *lapin, pos_t pos, int size, Color col)
  {
    Color *pixels = reinterpret_cast<Color *>(lapin->m_render->pixels);
    for (int y = 0; y < pos.y + size; y++)
    {
      for (int x = 0; x < pos.x + size; x++)
      {
        pixels[x + lapin->m_windowWeight * y] = col;
      }
    }
  }
}

extern "C"
{
  arcade::IGfxLib *getLib()
  {
    return (new arcade::libLapin());
  }
}
