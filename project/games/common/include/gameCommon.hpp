/*
** gameCommon.hpp for arcade in /home/login_p/delivery/arcade/gameCommon.hpp
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  dim. avr. 09 05:34:08 2017 Prenom Nom
** Last update dim. avr. 09 05:34:08 2017 Prenom Nom
*/

#ifndef GAME_COMMON_HPP_
 #define GAME_COMMON_HPP_

#include "Tile.hpp"
#include "GameState.hpp"
#include "Protocol.hpp"

namespace arcade
{
  enum DirGame{
    DIR_UP = 0,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_DOWN
  };
  struct PosGame{
    PosGame(int x, int y, DirGame dir, Tile const & mtile)
    {
      _x = x;
      _y = y;
      _dir = dir;
      _tile = mtile;
    };
    int _x;
    int _y;
    DirGame _dir;
    Tile _tile = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
		      {0, 0, 0, 0}, 0, 0, 0, 0);
  };

  size_t readHigh(const std::string & file);
  void writeHigh(const std::string & file, size_t high);
  void changeDir(PosGame &cpy, DirGame dir);
  DirGame oppositeDir(DirGame dir);
}
#endif /* !GAME_COMMON_HPP_ */