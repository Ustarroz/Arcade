/*
** SnakeGUI.cpp for arcade in /home/login_p/delivery/arcade/SnakeGUI.cpp
**
** Made by Edouard Puillandre
** Login   <edouard.puillandre@epitech.eu>
**
** Started on  sam. avr. 08 13:28:48 2017 Edouard Puillandre
** Last update sam. avr. 08 13:28:48 2017 Edouard Puillandre
*/

#include "SnakeGUI.hpp"

namespace arcade
{
  SnakeGUI::SnakeGUI()
  {
    //selected = std::vector<int>(3, 0);
    Component comp = Component({255,255,255,255}, "GameOver", 0.4, 0.25, GUI_WIDTH, GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "0", GUI_COL_THREE, GUI_LINE_THREE + GUI_STEP_LINE, GUI_WIDTH, GUI_HEIGHT);
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
    comp = Component({255,255,255,255}, "SDL", GUI_COL_TWO, GUI_LINE_THREE, GUI_WIDTH,GUI_HEIGHT);
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

  GameState SnakeGUI::useEventKeyBoardGUI(Event event, GameState state)
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
	  if (state == GameState::QUIT)
	    //m_comps.pop_back();
	  return (GameState::INGAME);
	default:
	  break;
      }
    return (state);
  }

  GameState SnakeGUI::useEventKeyButtonGUI(Event event, GameState state)
  {
    (void)event;
    return (state);
  }

  GameState SnakeGUI::useEventKeyJoystickGUI(Event event, GameState state)
  {
    (void)event;
    return (state);
  }

  GameState SnakeGUI::useEventGUI(Event event, GameState state)
  {
    if (state == GameState::QUIT && m_comps.size() != 11)
      {
	//m_comps[.setStringColor({0,0,0,255});
	return (GameState::QUIT);
      }
    switch (event.type)
      {
	case ET_KEYBOARD:
	  return (useEventKeyBoardGUI(event, state));
	case ET_JOYSTICK:
	  return (useEventKeyJoystickGUI(event, state));
	case ET_BUTTON:
	  return (useEventKeyButtonGUI(event, state));
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