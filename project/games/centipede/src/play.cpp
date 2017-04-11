#include <iostream>
#include <string.h>
#include <unistd.h>
#include "libCentipede.hpp"

namespace arcade
{
  extern "C"
  {
  void Play()
  {
    Centipede centipede;
    CommandType in;
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
	    std::cerr << "WHEREAMI" << std::endl;
#endif
            WhereAmI *ami = new WhereAmI [sizeof(WhereAmI) + (sizeof(Position))];
	    ami->type = CommandType::WHERE_AM_I;
	    ami->lenght = 1;
	    ami->position[0] = centipede.getPlayer();
#ifdef DEBUG
              std::cerr << "SIZEOF wrotte: " << sizeof(WhereAmI) + (sizeof(Position)) << std::endl;
#endif
              std::cout.write(reinterpret_cast<char *>(ami), sizeof(WhereAmI) + (sizeof(Position)));
#ifdef DEBUG
            std::cerr << "REALLY WROTE: " << std::endl;
#endif
#ifdef DEBUG
	    std::cerr << "END_WHEREAMI" << std::endl;
#endif
	  }
	else if (in == CommandType::GET_MAP)
	  {
#ifdef DEBUG
	    std::cerr << "GETMAP: height: " << centipede.getCurrentMap().getHeight() <<
              " Weight: " << centipede.getCurrentMap().getWidth() <<
             " sizeof(TileType): " << sizeof(TileType) <<  std::endl;
#endif
	    GetMap *getMap = reinterpret_cast<GetMap *>(new char[
	    sizeof(struct GetMap) +
	    sizeof(TileType) * centipede.getCurrentMap().getWidth() *
	    centipede.getCurrentMap().getHeight()]);
	    getMap->type = CommandType::GET_MAP;
	    getMap->width = centipede.getCurrentMap().getWidth();
	    getMap->height = centipede.getCurrentMap().getHeight();
	    for (size_t i = 0; i < getMap->height; ++i)
	      {
		for (size_t j = 0; j < getMap->width; ++j)
		  {
		    getMap->tile[i * getMap->width +
				 j] = dynamic_cast<const Tile &> (centipede.getCurrentMap().at(
		     0, j, i)).getType();
		  }
	      }
            std::cout.write(reinterpret_cast<char *>(getMap), sizeof(struct GetMap) +
			     sizeof(TileType) * centipede.getCurrentMap().getWidth() *
                             centipede.getCurrentMap().getHeight());
#ifdef DEBUG
	    std::cerr << "MAP: wrote: " << std::endl;
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
		centipede.notifyEvent(std::move(e_list));
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
		centipede.notifyEvent(std::move(e_list));
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
		centipede.notifyEvent(std::move(e_list));
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
		centipede.notifyEvent(std::move(e_list));
#ifdef DEBUG
	    std::cerr << "END_GO_RIGHT" << std::endl;
#endif
	  	}
	else if (in == CommandType::PLAY)
	      {
#ifdef DEBUG
	    std::cerr << "GO_PLAY" << std::endl;
#endif
		centipede.process();
#ifdef DEBUG
	    std::cerr << "END_GO_PLAY" << std::endl;
#endif
	      }
	if (centipede.getGameState() == GameState::QUIT)
	  break;
	  }
      }
  }
}
