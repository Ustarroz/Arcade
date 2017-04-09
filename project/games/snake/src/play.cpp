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
#ifdef DEBUG
	std::cerr << "CommandType: " << static_cast<int> (in) << std::endl;
#endif
	if (in == CommandType::WHERE_AM_I)
	  {
#ifdef DEBUG
	    std::cerr << "WHEREAMI: playerSize: " << snake.getPlayer().size() << std::endl;
#endif
	    //WhereAmI *ami = reinterpret_cast<WhereAmI *> (new char [sizeof(WhereAmI) + (sizeof(Position) * snake.getPlayer().size())]);
            WhereAmI *ami = new WhereAmI [sizeof(WhereAmI) + (sizeof(Position) * snake.getPlayer().size())];
            if (!ami)
            {
              return ;
            }
	    ami->type = CommandType::WHERE_AM_I;
	    ami->lenght = snake.getPlayer().size();
	    for (size_t i = 0; i < snake.getPlayer().size(); i++)
	      {
		ami->position[i] = snake.getPlayer()[i];
	      }
#ifdef DEBUG
              std::cerr << "SIZEOF wrotte: " << sizeof(WhereAmI) + (sizeof(Position) * snake.getPlayer().size()) << std::endl;
#endif
            int a = write(1, ami, sizeof(WhereAmI) + (sizeof(Position) * snake.getPlayer().size()));
#ifdef DEBUG
            std::cerr << "REALLY WROTE: " << a << std::endl;
#endif

	    	    /*WhereAmI *ami = new(WhereAmI [sizeof(struct WhereAmI) + sizeof(Position) * snake.getPlayer().size()]);
	    ami->type = CommandType::WHERE_AM_I;
	    ami->lenght = static_cast<uint16_t> (snake.getPlayer().size());
	    write_position(snake.getPlayer(), ami);
	    std::cout.write(reinterpret_cast<char*>(ami), sizeof(struct WhereAmI) + sizeof(Position) * snake.getPlayer().size());
	    std::cerr << "WHEREAMI" << std::endl;
	    delete(ami);*/
#ifdef DEBUG
	    std::cerr << "END_WHEREAMI" << std::endl;
#endif
	  }
	else if (in == CommandType::GET_MAP)
	  {
#ifdef DEBUG
	    std::cerr << "GETMAP: height: " << snake.getCurrentMap().getHeight() <<
              " Weight: " << snake.getCurrentMap().getWidth() <<
             " sizeof(TileType): " << sizeof(TileType) <<  std::endl;
#endif
	    GetMap *getMap = reinterpret_cast<GetMap *>(new char[
	    sizeof(struct GetMap) +
	    sizeof(TileType) * snake.getCurrentMap().getWidth() *
	    snake.getCurrentMap().getHeight()]);
	    getMap->type = CommandType::GET_MAP;
	    getMap->width = snake.getCurrentMap().getWidth();
	    getMap->height = snake.getCurrentMap().getHeight();
            int l = 0;
	    for (size_t i = 0; i < getMap->height; ++i)
	      {
		for (size_t j = 0; j < getMap->width; ++j)
		  {
		    getMap->tile[i * getMap->width +
				 j] = dynamic_cast<const Tile &> (snake.getCurrentMap().at(
		     0, j, i)).getType();
		  }
	      }
	    int a = write(1, getMap, sizeof(struct GetMap) +
			     sizeof(TileType) * snake.getCurrentMap().getWidth() *
                             snake.getCurrentMap().getHeight());
#ifdef DEBUG
	    std::cerr << "MAP: wrote: " <<  a << std::endl;
#endif
	    //delete (getMap);
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
