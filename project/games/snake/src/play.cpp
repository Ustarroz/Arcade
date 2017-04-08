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
  void write_map(IMap const &map, GetMap *tmp)
  {
    int i = -1;

    for (unsigned int y = 0; y < map.getWidth(); y++)
      for (unsigned int x = 0; x < map.getHeight(); x++)
	{
	  tmp->tile[++i] = dynamic_cast<const Tile &>(map.at(0, x, y)).getType();
	}
  }

  extern "C"
  {
  void Play()
  {
    Snake snake;
    CommandType in;
    size_t op;
    //GetMap *map;
    Position pos;
    //WhereAmI *ami;
    Event e;
    std::vector<Event> e_list;


    memset(&e, 0, sizeof(Event));
    while (1)
      {
	memset(&in, 0, sizeof(CommandType));
       std::cin.read(reinterpret_cast<char *>(&in), sizeof(in));
	if (in == CommandType::WHERE_AM_I)
	  {
	    std::cerr << "WHEREAMIBEGIN" << std::endl;
	    WhereAmI *ami = reinterpret_cast<WhereAmI *> (new char [sizeof(WhereAmI) + sizeof(Position) * snake.getPlayer().size()]);
	    ami->type = CommandType::WHERE_AM_I;
	    ami->lenght = snake.getPlayer().size();
	    for (size_t i = -1; i < snake.getPlayer().size(); ++i)
	      {
		ami->position[i] = snake.getPlayer()[i];
	      }
	    write(1, ami, sizeof(sizeof(WhereAmI) + sizeof(Position) * snake.getPlayer().size()));

	    	    /*WhereAmI *ami = new(WhereAmI [sizeof(struct WhereAmI) + sizeof(Position) * snake.getPlayer().size()]);
	    ami->type = CommandType::WHERE_AM_I;
	    ami->lenght = static_cast<uint16_t> (snake.getPlayer().size());
	    write_position(snake.getPlayer(), ami);
	    std::cout.write(reinterpret_cast<char*>(ami), sizeof(struct WhereAmI) + sizeof(Position) * snake.getPlayer().size());
	    std::cerr << "WHEREAMI" << std::endl;
	    delete(ami);*/
	      }
	else if (in == CommandType::GET_MAP)
	      {
	    std::cerr << "BEGIN" << std::endl;
	   	GetMap *getMap = reinterpret_cast<GetMap *>(new char [sizeof(struct GetMap) + sizeof(TileType) * snake.getCurrentMap().getWidth() * snake.getCurrentMap().getHeight()]);
	    	getMap->type = CommandType::GET_MAP;
	    	getMap->width = snake.getCurrentMap().getWidth();
	    	getMap->height = snake.getCurrentMap().getHeight();
	    for (size_t i = 0; i < getMap->height; ++i)
	      {
		for (size_t j = 0; j < getMap->width ; ++j)
		  {
		    getMap->tile[i * getMap->width + j] = dynamic_cast<const Tile &> (snake.getCurrentMap().at(0, j, i)).getType();
		  }
	      }
	    std::cerr << "READ0" << std::endl;
	    write(1, getMap, sizeof(struct WhereAmI) + sizeof(Position) * snake.getPlayer().size());
	    std::cerr << "READ1" << std::endl;
	    delete(getMap);
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