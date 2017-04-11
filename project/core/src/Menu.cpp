#include <algorithm>
#include <iostream>
#include "Menu.hpp"

namespace arcade
{
  Menu::Menu()
  {
    m_state = GameState::MENU;
    m_lib = 0;
    m_cursor = 0;
    m_game = MENU_POS_GAME;
    m_name = "NAM";

    Component comp = Component(MENU_COLOR_BOTH, "lib_arcade_caca.so", MENU_COL_1, MENU_LINE_1,
			       MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_BG, "lib_arcade_lapin.so", MENU_COL_1,  MENU_LINE_2,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_BG, "lib_arcade_sdl.so", MENU_COL_1,  MENU_LINE_3,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_SELECT, "lib_arcade_snake.so", MENU_COL_2,  MENU_LINE_1,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_BG, "lib_arcade_centipede.so", MENU_COL_2,  MENU_LINE_2,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_BG, "NAM", MENU_COL_3,  MENU_LINE_1,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_TITLE, "GRAPHICS", MENU_COL_1,  MENU_LINE_05,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_TITLE, "GAMES", MENU_COL_2,  MENU_LINE_05,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_TITLE, "NAME", MENU_COL_3,  MENU_LINE_05,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);

    comp = Component(MENU_COLOR_MAIN_TITLE, "Menu", MENU_COL_2,  MENU_LINE_0,
		     MENU_WIDTH, MENU_HEIGHT);
    comp.setStringColor(MENU_COLOR_TXT);
    m_gui.addComponent(comp);
  }

  Menu::~Menu()
  {
  }

  GameState Menu::getGameState() const
  {
    return (m_state);
  }


  void Menu::useEventKeyBoard(Event const &event)
  {
    if (event.kb_key >= KB_A && event.kb_key <= KB_Z)
      {
	if (m_name.size() < 3 && m_cursor == MENU_POS_NAME)
	  {
	    m_name.append(1, 'A' + event.kb_key - KB_A);
	    m_gui.getComponent(MENU_POS_NAME).setString(m_name);
	  }
	return ;
      }
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
	case KB_SPACE:
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
	case KB_ENTER:
	  {
	    m_state = GameState::INGAME;
	    return;
	  }
	case KB_BACKSPACE:
	  {
	    if (m_name.size() > 0 && m_cursor == MENU_POS_NAME)
	      {
		m_name.resize(m_name.size() - 1);
		m_gui.getComponent(MENU_POS_NAME).setString(m_name);
	      }
	  }
	default:
	  break;
      }
  }

  void Menu::useEventKeyButton(Event const &event)
  {
    (void)event;
  }

  void Menu::useEventKeyJoystick(Event const &event)
  {
    (void)event;
  }

  void Menu::useEvent(Event const &event)
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

  std::vector<std::pair<std::string, SoundType> > Menu::getSoundsToLoad() const
  {
    return (std::move(m_soundsName));
  }

  std::vector<Sound> Menu::getSoundsToPlay()
  {
    return (std::move(m_soundsPlay));
  }

  IGUI &Menu::getGUI()
  {
    return (m_gui);
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

  size_t Menu::setLib(std::string const & lib)
  {
    size_t pos_lib = 0;

    while (pos_lib < MENU_POS_GAME)
      {
	if (lib == "lib/" + m_gui.getComponent(pos_lib).getText() ||
	   lib == "./lib/" + m_gui.getComponent(pos_lib).getText())
	  break;
	++pos_lib;
      }
    if (pos_lib == m_lib || pos_lib >= MENU_POS_GAME)
      return 0;
    m_gui.getComponent(m_lib).setColor(MENU_COLOR_BG);
    m_gui.getComponent(pos_lib).setColor(MENU_COLOR_BOTH);
    m_lib = pos_lib;
    return (pos_lib);
  }

  void Menu::setGameState(GameState state)
  {
    m_state = state;
  }
}