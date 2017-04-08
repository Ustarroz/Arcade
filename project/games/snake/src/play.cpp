#include <iostream>
#include <string.h>
#include <unistd.h>
#include "libSnake.hpp"

template<typename T>
void write_struct(std::ostream& out, T& t)
{
  std::cout.write(reinterpret_cast<char*>(&t), sizeof(T));
}

namespace arcade
{
  void write_map(IMap const &map)
  {
    TileType test;

    for (unsigned int x = 0; x < map.getWidth(); x++)
      for (unsigned int y = 0; y < map.getHeight(); y++)
	{
	  test = dynamic_cast<const Tile &>(map.at(0, x, y)).getType();
	  write(1, &test, sizeof(TileType));
	}
  }

  void write_position(std::vector<Position> pos, WhereAmI *tmp)
  {
    std::vector<Position>::iterator it;

    int i = 0;
    it = pos.begin();
    while (it != pos.end())
      {
	tmp->position[i++] = *it;
	it++;
      }
  }

  extern "C"
  {
  void Play()
  {
    Snake snake;
    CommandType in;
    int op;
    GetMap map;
    Position pos;
    WhereAmI *ami;
    Event e;
    std::vector<Event> e_list;


    memset(&e, 0, sizeof(Event));
    while (1)
      {
	memset(&in, 0, sizeof(CommandType));
	//read(0, &in, sizeof(CommandType));

	std::cin.read(reinterpret_cast<char *>(&in), sizeof(in));
	std::cerr << "CommandType: " << static_cast<int> (in) << std::endl;
	if (in == CommandType::WHERE_AM_I)
	  {
	    std::cerr << "WHEREAMI" << std::endl;
	    WhereAmI *ami = new(WhereAmI [sizeof(WhereAmI) + sizeof(Position) * snake.getPlayer().size()]);
		ami->type = CommandType::WHERE_AM_I;
		ami->lenght = static_cast<uint16_t> (snake.getPlayer().size());
	    write_position(snake.getPlayer(), ami);
	    std::cout.write(reinterpret_cast<char*>(&ami), sizeof(WhereAmI) + sizeof(Position) * snake.getPlayer().size());
	      }
	else if (in == CommandType::GET_MAP)
	      {
	    std::cerr << "GETMAP" << std::endl;
		map.type = CommandType::GET_MAP;
		map.width = (uint16_t) snake.getCurrentMap().getWidth();
		map.height = (uint16_t) snake.getCurrentMap().getHeight();
		write_struct(std::cout, map);
		write_map(snake.getCurrentMap());
	      }
	else if (in == CommandType::GO_UP)
	      {
		e_list.clear();
		e.kb_key = KB_ARROW_UP;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
	      }
	else if  (in == CommandType::GO_DOWN)
	      {
		e_list.clear();
		e.kb_key = KB_ARROW_DOWN;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
	      }
	else if (in == CommandType::GO_LEFT)
	      {
		e_list.clear();
		e.kb_key = KB_ARROW_LEFT;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
	  	}
	else if (in == CommandType::GO_RIGHT)
	      {
		e_list.clear();
		e.kb_key = KB_ARROW_RIGHT;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
	  	}
	else if (in == CommandType::PLAY)
	      {
		snake.process();
	      }
	if (snake.getGameState() == GameState::QUIT)
	  break;
	  }
      }
  }
}