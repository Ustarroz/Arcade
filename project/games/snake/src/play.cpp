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
#ifdef DEBUG
	std::cerr << "CommandType: " << static_cast<int> (in) << std::endl;
#endif
	if (in == CommandType::WHERE_AM_I)
	  {
#ifdef DEBUG
	    std::cerr << "WHEREAMI" << std::endl;
#endif
	    WhereAmI *ami = new(WhereAmI [sizeof(WhereAmI) + sizeof(Position) * snake.getPlayer().size()]);
		ami->type = CommandType::WHERE_AM_I;
		ami->lenght = static_cast<uint16_t> (snake.getPlayer().size());
	    write_position(snake.getPlayer(), ami);
	    std::cout.write(reinterpret_cast<char*>(&ami), sizeof(WhereAmI) + sizeof(Position) * snake.getPlayer().size());
#ifdef DEBUG
	    std::cerr << "END_WHEREAMI" << std::endl;
#endif
	      }
	else if (in == CommandType::GET_MAP)
	      {
#ifdef DEBUG
	    std::cerr << "GETMAP" << std::endl;
#endif
		map.type = CommandType::GET_MAP;
		map.width = (uint16_t) snake.getCurrentMap().getWidth();
		map.height = (uint16_t) snake.getCurrentMap().getHeight();
		write_struct(std::cout, map);
		write_map(snake.getCurrentMap());
#ifdef DEBUG
	    std::cerr << "END_GETMAP" << std::endl;
#endif
	      }
	else if (in == CommandType::GO_UP)
	      {
#ifdef DEBUG
	    std::cerr << "GO_UP" << std::endl;
#endif
		e_list.clear();
		e.kb_key = KB_ARROW_UP;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
#ifdef DEBUG
	    std::cerr << "END_GO_UP" << std::endl;
#endif
	      }
	else if  (in == CommandType::GO_DOWN)
	      {
#ifdef DEBUG
	    std::cerr << "GO_DOWN" << std::endl;
#endif
		e_list.clear();
		e.kb_key = KB_ARROW_DOWN;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
#ifdef DEBUG
	    std::cerr << "END_GO_DOWN" << std::endl;
#endif
	      }
	else if (in == CommandType::GO_LEFT)
	      {
#ifdef DEBUG
	    std::cerr << "GO_LEFT" << std::endl;
#endif
		e_list.clear();
		e.kb_key = KB_ARROW_LEFT;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
#ifdef DEBUG
	    std::cerr << "END_GO_LEFT" << std::endl;
#endif
	  	}
	else if (in == CommandType::GO_RIGHT)
	      {
#ifdef DEBUG
	    std::cerr << "GO_RIGHT" << std::endl;
#endif
		e_list.clear();
		e.kb_key = KB_ARROW_RIGHT;
		e.action = AT_PRESSED;
		e_list.push_back(e);
		snake.notifyEvent(std::move(e_list));
#ifdef DEBUG
	    std::cerr << "END_GO_RIGHT" << std::endl;
#endif
	  	}
	else if (in == CommandType::PLAY)
	      {
#ifdef DEBUG
	    std::cerr << "GO_PLAY" << std::endl;
#endif
		snake.process();
#ifdef DEBUG
	    std::cerr << "END_GO_PLAY" << std::endl;
#endif
	      }
	if (snake.getGameState() == GameState::QUIT)
	  break;
	  }
      }
  }
}