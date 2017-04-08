/*
** CentipedeGUI.hpp.hpp for arcade in /home/login_p/delivery/arcade/CentipedeGUI.hpp.hpp
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  sam. avr. 08 13:28:10 2017 Prenom Nom
** Last update sam. avr. 08 13:28:10 2017 Prenom Nom
*/

#ifndef CENTIPEDEGUI_HPP_
#define CENTIPEDEGUI_HPP_

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

namespace arcade
{
  class CentipedeGUI: public GUI
  {
    GameState useEventKeyBoardGUI(Event event, GameState state);
    GameState useEventKeyJoystickGUI(Event event, GameState state);
    GameState useEventKeyButtonGUI(Event event, GameState state);
   public:
    CentipedeGUI();
    ~CentipedeGUI();
    GameState useEventGUI(Event event, GameState state);
    void setScore(size_t score);
  };
}

#endif /* !CENTIPEDEGUI_HPP_ */