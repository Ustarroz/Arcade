#include <iostream>
#include "libSnake.hpp"


template<typename T>
void write_struct(std::ostream& out, T& t)
{
  std::cout.write(reinterpret_cast<char*>(&t), sizeof(T));
}

namespace arcade
{

  void	write_map()
  {

  }

  void	write_position(std::vector<Position> pos)
  {
    std::vector<Position>::iterator it;

    it = pos.begin();
    while (it != pos.end())
      {
	write_struct(std::cout, *it);
	it++;
      }
  }

void Play()
{
  Snake snake;
  std::string in;
  int op;
  GetMap map;
  Position pos;
  WhereAmI ami;
  Event e;
  std::vector<Event> e_list;

  memset(&e, 0, sizeof(Event));
  while (1)
    {
      std::cin >> in;
      op = std::stoi(in);
      switch (op)
      {
	case 0:
	  {
	    ami.type = (CommandType) 0;
	    ami.lenght = (uint16_t)(snake.getCurrentMap().getWidth() + snake.getCurrentMap().getHeight());
	    write_struct(std::cout, ami);
	    write_position(snake.getPlayer());
	  }
	case 1:
	  {
	    map.type = (CommandType) 1;
	    map.width = (uint16_t)snake.getCurrentMap().getWidth();
	    map.height = (uint16_t)snake.getCurrentMap().getHeight();
	    write_struct(std::cout, map);
	    //write_map(snake.getCurrentMap());
	  }
	case 2:
	  {
	    e_list.clear();
	    e.kb_key = KB_ARROW_UP;
	    e.action = AT_PRESSED;
	    e_list.push_back(e);
	    snake.notifyEvent(std::move(e_list));
	  }
	case 3:
	  {
	    e_list.clear();
	    e.kb_key = KB_ARROW_DOWN;
	    e.action = AT_PRESSED;
	    e_list.push_back(e);
	    snake.notifyEvent(std::move(e_list));
	  }
	case 4:
	  {
	    e_list.clear();
	    e.kb_key = KB_ARROW_LEFT;
	    e.action = AT_PRESSED;
	    e_list.push_back(e);
	    snake.notifyEvent(std::move(e_list));
	  }
	case 5:
	  {
	    e_list.clear();
	    e.kb_key = KB_ARROW_RIGHT;
	    e.action = AT_PRESSED;
	    e_list.push_back(e);
	    snake.notifyEvent(std::move(e_list));
	  }
	case 9;
	{
	  snake.process();
	}
	default:
	  {

	  }
      }
    }
}
}