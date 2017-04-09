/*
** gameCommon.cpp for arcade in /home/login_p/delivery/arcade/gameCommon.cpp
**
** Made by Prenom Nom
** Login   <prenom.nom@epitech.eu>
**
** Started on  dim. avr. 09 05:38:53 2017 Prenom Nom
** Last update dim. avr. 09 05:38:53 2017 Prenom Nom
*/

#include <fstream>
#include <iostream>
#include "gameCommon.hpp"

namespace arcade
{
  size_t readHigh(const std::string & file)
  {
    std::ifstream myfile;
    std::string line;
    int 	nb;

    myfile.open(file);
    if (!myfile.is_open())
      return (0);
    getline(myfile, line);
    if (line.size() == 0)
      {
	myfile.close();
	return (0);
      }
    try {
	nb = stoi(line);
      }
    catch (std::invalid_argument){
	return (0);
      }
    myfile.close();
    return (nb < 0 ? 0 : nb);
  }

  void writeHigh(const std::string & file, size_t high)
  {
    std::ofstream myfile;
    std::string line;

    myfile.open(file, std::ios::trunc);
    if (!myfile.is_open())
      return ;
    line = std::to_string(high);
    myfile << line;
    myfile.close();
  }

  DirGame oppositeDir(DirGame dir)
  {
    switch (dir)
      {
	case DIR_UP:
	  return (DIR_DOWN);
	case DIR_DOWN:
	  return (DIR_UP);
	case DIR_LEFT:
	  return (DIR_RIGHT);
	case DIR_RIGHT:
	  return (DIR_LEFT);
	default:
	  return (DIR_UP);
      }
  }

  void changeDir(PosGame &cpy, DirGame dir)
  {
    switch (dir)
      {
	case DIR_RIGHT :
	  cpy._x = cpy._x + 1;
	break;
	case DIR_LEFT :
	  cpy._x = cpy._x - 1;
	break;
	case DIR_UP :
	  cpy._y = cpy._y - 1;
	break;
	case DIR_DOWN :
	  cpy._y = cpy._y + 1;
	break;
      }
  }


}