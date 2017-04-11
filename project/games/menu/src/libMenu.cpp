#include <algorithm>
#include <iostream>
#include "libMenu.hpp"

namespace arcade
{
  Menu::Menu()
    : m_map(0, 0)
  {
    m_state = GameState::INGAME;
    m_lib = 0;
    m_cursor = 0;
    m_game = MENU_POS_GAME;

    Component comp = Component(MENU_COLOR_BOTH, "Caca", MENU_COL_1, MENU_LINE_1,
			       MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_BG, "Lapin", MENU_COL_1,  MENU_LINE_2,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_BG, "SDL", MENU_COL_1,  MENU_LINE_3,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_SELECT, "Snake", MENU_COL_2,  MENU_LINE_1,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_BG, "Centipede", MENU_COL_2,  MENU_LINE_2,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_BG, "NAM", MENU_COL_3,  MENU_LINE_1,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_TITLE, "GRAPHICS", MENU_COL_1,  MENU_LINE_05,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_TITLE, "GAMES", MENU_COL_2,  MENU_LINE_05,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_TITLE, "NAME", MENU_COL_3,  MENU_LINE_05,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);

    comp = Component(MENU_COLOR_MAIN_TITLE, "Menu", MENU_COL_2,  MENU_LINE_0,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
    pos.push_back(comp);
  }

  Menu::~Menu()
  {
  }

  GameState Menu::getGameState() const
  {
    return (m_state);
  }


  void Menu::useEventKeyBoard(Event event)
  {
    switch (event.kb_key)
      {
	case KB_ARROW_LEFT:
	  {
	    if (m_cursor > 0)
	      {
		if (m_cursor == m_game || m_cursor == m_lib)
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_SELECT);
		else
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_BG);
		--m_cursor;
		if (m_cursor == m_game || m_cursor == m_lib)
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_BOTH);
		else
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_CURSOR);
	      }
	    break;
	  }
	case KB_ARROW_RIGHT:
	  {
	    if (m_cursor < MENU_POS_NAME)
	      {
		if (m_cursor == m_game || m_cursor == m_lib)
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_SELECT);
		else
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_BG);
		++m_cursor;
		if (m_cursor == m_game || m_cursor == m_lib)
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_BOTH);
		else
		  m_gui.getComponent(m_cursor).setColor(MENU_COLOR_CURSOR);
	      }
	    break;
	  }
	case KB_ESCAPE:
	  {
	    m_state = GameState::QUIT;
	    return;
	  }
	case KB_ENTER:
	  {
	    if (m_cursor < MENU_POS_GAME)
	      {
		m_gui.getComponent(m_lib).setColor(MENU_COLOR_BG);
		m_gui.getComponent(m_cursor).setColor(MENU_COLOR_BOTH);
		m_lib = m_cursor;
	      }
	    else if (m_cursor >= MENU_POS_GAME && m_cursor < MENU_POS_NAME)
	      {
		m_gui.getComponent(m_game).setColor(MENU_COLOR_BG);
		m_gui.getComponent(m_cursor).setColor(MENU_COLOR_BOTH);
		m_game = m_cursor;
	      }
	    break;
	  }
	default:
	  break;
      }
  }

  void Menu::useEventKeyButton(Event event)
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
	case ET_QUIT:
	  m_state = GameState::QUIT;
	default:
	  break;
      }
  }

  void Menu::notifyEvent(std::vector<Event> &&event)
  {
    for(std::vector<Event>::iterator it = event.begin();
	it != event.end(); ++it)
      {
	useEvent(*it);
      }
  }

  void Menu::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
    (void)events;
  }

  std::vector<NetworkPacket> Menu::getNetworkToSend()
  {
    return (std::move(m_net));
  }

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

  bool Menu::hasNetwork() const
  {
    return false;
  }

  std::string const & Menu::getGame()
  {
    return (m_gui.getComponent(m_game).getText());
  }

  std::string const & Menu::getLib()
  {
    return (m_gui.getComponent(m_lib).getText());
  }

  std::string const & Menu::getName()
  {
    return (m_gui.getComponent(MENU_POS_NAME).getText());
  }
}

extern "C"
{
arcade::IGame *getGame()
{
  return (new arcade::Menu());
}
}
