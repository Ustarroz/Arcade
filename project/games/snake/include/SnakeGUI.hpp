/*
** SnakeGUI.hpp.hpp for arcade in /home/login_p/delivery/arcade/SnakeGUI.hpp.hpp
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  sam. avr. 08 13:28:10 2017 Prenom Nom
** Last update sam. avr. 08 13:28:10 2017 Prenom Nom
*/

#ifndef SNAKEGUI_HPP_
#define SNAKEGUI_HPP_

#include "Event.hpp"
#include "GUI.hpp"

#define GUI_COL_ONE 0.1
#define GUI_COL_TWO 0.4
#define GUI_COL_THREE 0.7
#define GUI_LINE_ONE 0.65
#define GUI_LINE_TWO 0.75
#define GUI_LINE_THREE 0.85
#define GUI_STEP_LINE 0.04
#define GUI_WIDTH 160
#define GUI_HEIGHT 17
#define GUI_CURSOR 0
#define GUI_SELECTED_ONE 1
#define GUI_SELECTED_TWO 2
#define GUI_SCORE 3
#define GUI_HIGHSCORE 4
#define GUI_NAME 5
#define GUI_GAMEOVER 6

namespace arcade
{
  struct ButtonSelected
  {

  };

  class SnakeGUI: public GUI
  {
    int posx;
    int posy;
    std::vector<int> selected;
    GameState useEventKeyBoardGUI(Event event, GameState state);
    GameState useEventKeyJoystickGUI(Event event, GameState state);
    GameState useEventKeyButtonGUI(Event event, GameState state);
   public:
    SnakeGUI();
    ~SnakeGUI();
    GameState useEventGUI(Event event, GameState state);
    void setScore(size_t score);
  };
}

#endif /* !SNAKEGUI_HPP_ */