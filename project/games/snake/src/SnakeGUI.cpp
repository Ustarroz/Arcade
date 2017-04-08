/*
** SnakeGUI.cpp for arcade in /home/login_p/delivery/arcade/SnakeGUI.cpp
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  sam. avr. 08 13:28:48 2017 Prenom Nom
** Last update sam. avr. 08 13:28:48 2017 Prenom Nom
*/

#include "SnakeGUI.hpp"

namespace arcade
{
  SnakeGUI::SnakeGUI()
  {
    Component comp = Component({255,255,255,255}, "0", GUI_COL_THREE, GUI_LINE_THREE + GUI_STEP_LINE, GUI_WIDTH, GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "0", GUI_COL_THREE, GUI_LINE_TWO + GUI_STEP_LINE, GUI_WIDTH, GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "name", GUI_COL_THREE, GUI_LINE_ONE, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Score", GUI_COL_THREE, GUI_LINE_THREE, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "HighScore", GUI_COL_THREE, GUI_LINE_TWO, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Caca", GUI_COL_TWO, GUI_LINE_ONE, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Lapin", GUI_COL_TWO, GUI_LINE_TWO, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "SDL", GUI_COL_ONE, GUI_LINE_THREE, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Snake", GUI_COL_ONE, GUI_LINE_ONE, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Centipede", GUI_COL_ONE, GUI_LINE_TWO, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
  }

  SnakeGUI::~SnakeGUI()
  {
  }

  GameState SnakeGUI::useEventKeyBoardGUI(Event event)
  {
    switch (event.kb_key)
      {
	case KB_ARROW_LEFT:

	  break;
	case KB_ARROW_RIGHT:

	  break;
	case KB_ARROW_DOWN:

	  break;
	case KB_ARROW_UP:

	  break;
	case KB_ENTER:
	  return (GameState::INGAME);
	default:
	  break;
      }
    return (GameState::MENU);
  }

  GameState SnakeGUI::useEventKeyButtonGUI(Event event)
  {
    (void)event;
    return (GameState::MENU);
  }

  GameState SnakeGUI::useEventKeyJoystickGUI(Event event)
  {
    (void)event;
    return (GameState::MENU);
  }

  GameState SnakeGUI::useEventGUI(Event event, GameState state)
  {
    switch (event.type)
      {
	case ET_KEYBOARD:
	  return (useEventKeyBoardGUI(event));
	case ET_JOYSTICK:
	  return (useEventKeyJoystickGUI(event));
	case ET_BUTTON:
	  return (useEventKeyButtonGUI(event));
	default:
	  break;
      }
    return (state);
  }

  void SnakeGUI::setScore(size_t score)
  {
    m_comps[0].setString(std::to_string(score));
  }
}