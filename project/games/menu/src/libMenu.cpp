#include <algorithm>
#include <string>
#include "libMenu.hpp"
#include "Map.hpp"
#include "GameState.hpp"
#include "Tile.hpp"
#include <iostream>

namespace arcade
{
  Menu::Menu()
    : m_map(64, 40)
  {
    m_map.addLayer();
    Tile bg = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
        {84, 84, 84, 255}, 0, 0, 0, 0);
    for (int x = 10; x < 50; x++)
    {
      for (int y = 8; y < 24; y++)
      {
        m_map.setTile(0, x, y, bg);
      }
    }
    Component comp = Component({255,255,255,255}, "0", 0.7, 0.77,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "0", 0.7, 0.86,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "Score", 0.7, 0.82,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "HighScore", 0.7, 0.73,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "Caca", 0.4, 0.73,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "Lapin", 0.4, 0.82,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "SDL", 0.4, 0.91,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "Menu", 0.1, 0.73,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
    comp = Component({255,255,255,255}, "Centipede", 0.1, 0.82,160,17);
    comp.setStringColor({0,0,0,255});
    m_gui.addComponent(comp);
  }

  Menu::~Menu()
  {
  }


  GameState Menu::getGameState() const
  {
    return (GameState::INGAME);
  }

  /*void Menu::useEventKeyBoard(Event event)
    {
    switch (event.kb_key)
    {
    case KB_ARROW_LEFT:
    m_dir[0]._dir = m_dir[0]._dir != DIR_RIGHT ? DIR_LEFT : DIR_RIGHT;
    break;
    case KB_ARROW_RIGHT:
    m_dir[0]._dir = m_dir[0]._dir == DIR_LEFT ? DIR_LEFT : DIR_RIGHT;
    break;
    case KB_ARROW_DOWN:
    m_dir[0]._dir = m_dir[0]._dir == DIR_UP ? DIR_UP : DIR_DOWN;
    break;
    case KB_ARROW_UP:
    m_dir[0]._dir = m_dir[0]._dir != DIR_DOWN ? DIR_UP : DIR_DOWN;
    break;
    default:
    break;
    }
    }*/

  /*void Menu::useEventKeyButton(Event event)
    {
    (void)event;
    }

    void Menu::useEventKeyJoystick(Event event)
    {
    (void)event;
    }

    void Menu::useEvent(Event event)
    {
    switch (event.type)
    {
    case ET_KEYBOARD:
    useEventKeyBoard(event);
    break;
    case ET_JOYSTICK:
    useEventKeyJoystick(event);
    break;
    case ET_BUTTON:
    useEventKeyButton(event);
    break;
    default:
    break;
    }
    }*/

  void Menu::notifyEvent(std::vector<Event> &&event)
  {
    /*for(std::vector<Event>::iterator it = event.begin();
      it != event.end(); ++it)
      {
      this->useEvent(*it);
      }*/
  }

  void Menu::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
    (void)events;
  }

  std::vector<NetworkPacket> &&Menu::getNetworkToSend()
  {
    return (std::move(m_net));
  }

  /*static Menu::DirMenu oppositeDir(Menu::DirMenu dir)
    {
    switch (dir)
    {
    case Menu::DIR_UP:
    return (Menu::DIR_DOWN);
    case Menu::DIR_DOWN:
    return (Menu::DIR_UP);
    case Menu::DIR_LEFT:
    return (Menu::DIR_RIGHT);
    case Menu::DIR_RIGHT:
    return (Menu::DIR_LEFT);
    default:
    return (Menu::DIR_UP);
    }
    }

    static void changeDir(Menu::PosMenu &cpy, Menu::DirMenu dir)
    {
    switch (dir)
    {
    case Menu::DIR_RIGHT :
    cpy._x = cpy._x + 1;
    break;
    case Menu::DIR_LEFT :
    cpy._x = cpy._x - 1;
    break;
    case Menu::DIR_UP :
    cpy._y = cpy._y - 1;
    break;
    case Menu::DIR_DOWN :
    cpy._y = cpy._y + 1;
    break;
    }
    }*/

  void Menu::process()
  {
  }

  std::vector<std::unique_ptr<ISprite>> Menu::getSpritesToLoad() const
  {
    std::vector<std::unique_ptr<ISprite> > sprites;
    return (std::move(sprites));
  }

  std::vector<std::pair<std::string, SoundType> > Menu::getSoundsToLoad() const
  {
    return (std::move(m_soundsName));
  }

  std::vector<Sound> Menu::getSoundsToPlay()
  {
    return (std::move(m_soundsPlay));
  }

  IMap const &Menu::getCurrentMap() const
  {
    return (m_map);
  }

  IGUI &Menu::getGUI()
  {
    return (m_gui);
  }

  extern "C"
  {
    arcade::IGame *getGame()
    {
      return (new arcade::Menu());
    }
  }
}
