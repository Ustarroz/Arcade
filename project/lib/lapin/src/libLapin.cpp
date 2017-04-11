#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "libLapin.hpp"
#include "Common.hpp"
#include "ITile.hpp"
#include "lapin.h"
#include "lapin/enum.h"

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
    m_prog.name = "Arcade";
    m_render = bunny_new_pixelarray(m_windowWeight, m_windowHeight);
    if (m_prog.win == NULL)
      {
	bunny_printlerr("Cannot open the window.");
	return (1);
	exit(1);
      }
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
	  static bool a = false;
	  a = !a;
	  m_event = &e;
	   bunny_set_key_response(libLapin::_bunnyPollEvent);
    bunny_set_loop_main_function(libLapin::_bunnyPollEventLoop);
    bunny_loop(m_prog.win, 6000, this);
    return (a);
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
    m_map = &map;
    bunny_set_loop_main_function(libLapin::_bunnyUpdateMap);
    bunny_loop(m_prog.win, 60, this);
  }

  void libLapin::updateGUI(IGUI &gui)
  {
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
#ifdef DEBUG
    std::cout << "[Lapin] updating map" << std::endl;
#endif
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
#ifdef DEBUG
    std::cout << "[Lapin] END updating map" << std::endl;
#endif
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response libLapin::_bunnyUpdateGUI(void *data)
  {
#ifdef DEBUG
    std::cout << "[Lapin] updating GUI" << std::endl;
#endif
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
#ifdef DEBUG
    std::cout << "[Lapin] DISPLAY" << std::endl;
#endif
    libLapin *lapin = static_cast<libLapin *>(data);
    bunny_blit(&lapin->m_prog.win->buffer, &lapin->m_render->clipable, NULL);
    bunny_display(lapin->m_prog.win);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response libLapin::_bunnyClear(void *data)
  {
#ifdef DEBUG
    std::cout << "[Lapin] CLEAR" << std::endl;
#endif
    libLapin *lapin = static_cast<libLapin *>(data);
    Color *pixels = reinterpret_cast<Color *>(lapin->m_render->pixels);
    std::memset(pixels, PINK2, lapin->m_windowWeight * lapin->m_windowHeight * sizeof(Color));
    //bunny_clear(&lapin->m_render->clipable.buffer, BLACK);
    //bunny_blit(&lapin->m_prog.win->buffer, &lapin->m_render->clipable, NULL);
    //bunny_display(lapin->m_prog.win);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response libLapin::_bunnyPollEventLoop(void *data)
  {
#ifdef DEBUG
    std::cout << "[Lapin] PollEventLoop" << std::endl;
#endif
    libLapin *lapin = static_cast<libLapin *>(data);
    return (EXIT_ON_SUCCESS);
  }

  t_bunny_response	libLapin::_bunnyPollEvent(t_bunny_event_state	state,
				     t_bunny_keysym		sym,
				     void			*data)
  {
    libLapin *lapin = static_cast<libLapin *>(data);
	  switch (state)
	  {
		  case GO_DOWN:
			  for (std::map<e_bunny_keysym, KeyboardKey>::iterator it = lapin->m_keys.begin(); it != lapin->m_keys.end(); ++it)
			  {
				  if (sym == it->first)
				  {
					  if (it->first == BKS_ESCAPE)
					  {
						  lapin->m_event->type = ET_QUIT;
						  lapin->m_event->action = AT_PRESSED;
						  lapin->m_event->kb_key = it->second;
						  return (EXIT_ON_SUCCESS);
					  }
					  lapin->m_event->type = ET_KEYBOARD;
					  lapin->m_event->action = AT_PRESSED;
					  lapin->m_event->kb_key = it->second;
					  return (EXIT_ON_SUCCESS);
				  }
			  }
			  break;
		  default:
			  lapin->m_event->type = ET_NONE;
			  lapin->m_event->action = AT_NONE;
			  lapin->m_event->kb_key = KB_NONE;
			  break;
	  }
	  return (EXIT_ON_SUCCESS);
  }

  void libLapin::drawSquare(libLapin *lapin, pos_t pos, int size, Color col)
  {
	  Color *pixels = reinterpret_cast<Color *>(lapin->m_render->pixels);
	  for (int y = pos.y; y < pos.y + size; y++)
	  {
		  for (int x = pos.x; x < pos.x + size; x++)
		  {
			  int ndx = x + lapin->m_windowWeight * y;
			  Color oldColor;
			    oldColor.a = pixels[ndx].a;
			    oldColor.r = pixels[ndx].r;
			    oldColor.g = pixels[ndx].g;
			    oldColor.b = pixels[ndx].b;
			    double alpha = col.a / 255.0;
			    Color newColor;
			    newColor.r = col.r * alpha + oldColor.r * (1 - alpha);
			    newColor.g = col.g * alpha + oldColor.g * (1 - alpha);
			    newColor.b = col.b * alpha + oldColor.b * (1 - alpha);
			    newColor.a = col.a + oldColor.a * (1 - alpha);
			  pixels[ndx] = newColor;
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
