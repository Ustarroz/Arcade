/*
** GameGUI.cpp for arcade in /home/login_p/delivery/arcade/GameGUI.cpp
**
** Made by Edouard Puillandre
** Login   <edouard.puillandre@epitech.eu>
**
** Started on  sam. avr. 08 13:28:48 2017 Edouard Puillandre
** Last update sam. avr. 08 13:28:48 2017 Edouard Puillandre
*/

#include "GameGUI.hpp"

namespace arcade
{
  GameGUI::GameGUI()
  {
    Component comp = Component({255,255,255,255}, "0", GUI_COL_THREE, GUI_LINE_TWO + GUI_STEP_LINE, GUI_WIDTH, GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "0", GUI_COL_TWO, GUI_LINE_TWO + GUI_STEP_LINE, GUI_WIDTH, GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "name", GUI_COL_ONE, GUI_LINE_TWO, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "", 0.4, 0.25, GUI_WIDTH, 0);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Score", GUI_COL_THREE, GUI_LINE_TWO, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "HighScore", GUI_COL_TWO, GUI_LINE_TWO, GUI_WIDTH,GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
    comp = Component({255,255,255,255}, "Game", GUI_COL_TWO, GUI_LINE_ONE, GUI_WIDTH, GUI_HEIGHT);
    comp.setStringColor({0,0,0,255});
    m_comps.push_back(comp);
  }

  GameGUI::~GameGUI()
  {
  }

  void GameGUI::setGameOver(bool print_over, const std::string &text)
  {
    if (print_over)
      {
	m_comps[GUI_GAMEOVER].setWidth(text.size() * 10);
	m_comps[GUI_GAMEOVER].setHeight(GUI_HEIGHT);
	m_comps[GUI_GAMEOVER].setString(text);
      }
    else
      {
	m_comps[GUI_GAMEOVER].setHeight(0);
	m_comps[GUI_GAMEOVER].setString("");
      }
  }

  void GameGUI::setScore(size_t score)
  {
    m_comps[GUI_SCORE].setString(std::to_string(score));
  }

  void GameGUI::setHighScore(size_t score)
  {
    m_comps[GUI_HIGHSCORE].setString(std::to_string(score));
  }
}