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
#define GUI_STEP_LINE 0.04
#define GUI_WIDTH 160
#define GUI_GAME_OVER_WIDTH 80
#define GUI_HEIGHT 17

namespace arcade
{
  class SnakeGUI: public GUI
  {
    enum compId
    {
      GUI_SCORE = 0,
      GUI_HIGHSCORE,
      GUI_NAME,
      GUI_GAMEOVER
    };
   public:
    SnakeGUI();
    ~SnakeGUI();
    void setScore(size_t score);
    void setHighScore(size_t score);
    void setGameOver(bool print_over, const std::string & text = "");
  };
}

#endif /* !SNAKEGUI_HPP_ */