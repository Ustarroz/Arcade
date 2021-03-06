#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <caca.h>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "ITile.hpp"
#include "libCaca.hpp"

namespace arcade
{
  libCaca::libCaca()
    : m_windowHeight(320), m_windowWeight(320), m_doesSupportSound(false),
	m_disp(NULL), m_canvas(NULL)
  {
    initCaca();
  }

  libCaca::libCaca(int height, int weight)
    : m_windowHeight(height), m_windowWeight(weight), m_doesSupportSound(false),
	m_disp(NULL), m_canvas(NULL)
  {
    initCaca();
  }

  libCaca::~libCaca()
  {
    caca_free_display(m_disp);
  }

  int libCaca::initCaca()
  {
    m_canvas = caca_create_canvas(m_windowHeight, m_windowWeight);
    m_disp = caca_create_display(m_canvas);
    caca_set_color_ansi(m_canvas, CACA_BLACK, CACA_WHITE);
    return (0);
  }

  bool libCaca::pollEvent(Event &e)
  {
    caca_event_t event;
    if (caca_get_event(m_disp, CACA_EVENT_KEY_PRESS, &event, 0))
    {
      int key = caca_get_event_key_ch(&event);
#ifdef DEBUG
      std::cout << "KEY: " << key << std::endl;
#endif
     for (std::map<int, KeyboardKey>::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
     {
       if (key == it->first)
       {
         if (key == 27)
         {
           e.type = ET_QUIT;
           e.action = AT_PRESSED;
           e.kb_key = it->second;
           return (true);
         }
         e.type = ET_KEYBOARD;
         e.action = AT_PRESSED;
         e.kb_key = it->second;
         return (true);
       }
     }
     return (true);
    }
    else if (caca_get_event(m_disp, CACA_EVENT_KEY_RELEASE, &event, 0))
    {
      int key = caca_get_event_key_ch(&event);
#ifdef DEBUG
      std::cout << "KEY: " << key << std::endl;
#endif
     for (std::map<int, KeyboardKey>::iterator it = m_keys.begin(); it != m_keys.end(); ++it)
     {
       if (key == it->first)
       {
         e.type = ET_KEYBOARD;
         e.action = AT_RELEASED;
         e.kb_key = it->second;
         return (true);
       }
     }
     return (true);
    }
    else
      return (false);
  }

  bool libCaca::doesSupportSound() const
  {
    //return (m_doesSupportSound);
    return (false);
  }

  void libCaca::loadSounds(std::vector<std::pair<std::string, SoundType> > const &sound)
  {
    (void)sound;
#ifdef DEBUG
    std::cout << "[Caca] LOAD SOUNDS" << std::endl;
#endif
  }

  void libCaca::soundControl(const Sound &sound)
  {
    (void)sound;
#ifdef DEBUG
    std::cout << "[Caca] SOUND CONTROL" << std::endl;
#endif
  }

  void libCaca::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    (void)sprites;
#ifdef DEBUG
    std::cout << "[Caca] LOAD SPRITES" << std::endl;
#endif
  }

  void libCaca::updateMap(IMap const &map)
  {
#ifdef DEBUG
    std::cout << "[Caca] Layer: " << map.getLayerNb() << ", y: " << map.getHeight() << ", x: " << map.getWidth() << std::endl;
#endif
    for (size_t nb = 0; nb < map.getLayerNb(); nb++)
    {
      for (size_t y = 0; y < map.getHeight(); y++)
      {
        for (size_t x = 0; x < map.getWidth(); x++)
        {
          ITile const &tile = map.at(nb, x, y);
          Color a = tile.getColor();
          pos_t pos = {static_cast<int>(x), static_cast<int>(y)};
          uint16_t u = 0;
	    u += a.a * 15 / 255 << 12;
	    u += a.r * 15 / 255 << 8;
	    u += a.g * 15 / 255 << 4;
	    u += a.b * 15 / 255 << 0;
#ifdef DEBUG
          //std::cout << "Color: " << u << std::endl;
#endif
          caca_set_color_argb(m_canvas, CACA_BLACK, u);
          drawSquare(pos, 1);
          caca_set_color_ansi(m_canvas, CACA_BLACK, CACA_WHITE);
        }
      }
    }
  }

  void libCaca::updateGUI(IGUI &gui)
  {
    for (size_t nb = 0; nb < gui.size(); nb++)
    {
      IComponent &c = gui.at(nb);
#ifdef DEBUG
      std::cout << c.getText() << std::endl;
#endif
      pos_t pos = {static_cast<int>(static_cast<double>(50) * c.getX()), static_cast<int>(static_cast<double>(30) * c.getY())};
	Color a = c.getBackgroundColor();
	uint16_t u = 0;
	u += a.a * 15 / 255 << 12;
	u += a.r * 15 / 255 << 8;
	u += a.g * 15 / 255 << 4;
	u += a.b * 15 / 255 << 0;
	a = c.getTextColor();
	uint16_t v = 0;
	v += a.a * 15 / 255 << 12;
	v += a.r * 15 / 255 << 8;
	v += a.g * 15 / 255 << 4;
	v += a.b * 15 / 255 << 0;
        caca_set_color_argb(m_canvas, v, u);
	caca_put_str(m_canvas, pos.x, pos.y, c.getText().c_str());
	caca_set_color_argb(m_canvas, CACA_BLACK, CACA_BLACK);
    }
  }

    void libCaca::display()
    {
#ifdef DEBUG
      std::cout << "[Caca] refresh screen" << std::endl;
#endif
      caca_refresh_display(m_disp);
    }

    void libCaca::clear()
    {
	    caca_clear_canvas(m_canvas);
      //clear caca
    }

    void libCaca::drawSquare(pos_t pos, int size)
    {
      for (int y = pos.y; y < pos.y + size; y++)
	{
	  for (int x = pos.x; x < pos.x + size; x++)
	    {
	      caca_put_str(m_canvas, x, y, " ");
	    }
	}
    }
  }

  extern "C"
  {
    arcade::IGfxLib *getLib()
    {
      return (new arcade::libCaca());
    }
  }
