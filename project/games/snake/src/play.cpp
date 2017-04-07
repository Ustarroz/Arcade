#include <iostream>
#include "Protocol.hpp"
#include "Event.hpp"

template<typename T>
void write_struct(std::ostream& out, T& t)
{
  std::cout.write(reinterpret_cast<char*>(&t), sizeof(T));
}


void play()
{
  std::string in;
  int op;
  GetMap map;
  Position pos;
  WhereAmI ami;
  Event	e;
  std::vector<Event> e_list;

  memset(&e, 0, sizeof(Event));
  while (1)
    {
      std::cin >> in;
      op = std::stoi(in);
      switch (op);
      {
	case 0:
	  {
	    ami.type = WHERE_AM_I;
	    ami.lenght = snake::getCurrentMap().getWidth();
	    ami.position = fill_position;
	    m_libsGame[0]->process();
	    write_struct(std::cout ,ami);
	  }
	case 1:
	  {
	    map.type = GET_MAP;
	    map.width = ;
	    map.height = ;
	    map.tile[];
	    m_libsGame[0]->process();
	  }
	case 2:
	  {
	    e_list.clear();
	    e_list.push_back();
	    m_libsgame[0]->notifyEvent()
	  }
	case 3:
	  {

	  }
	case 4:
	  {

	  }
	case 5:
	  {

	  }
	case 6:
	  {

	  }
	case 7:
	  {

	  }
	case 8:
	  {

	  }
	case 9;
	{

	}
	default:
	  {

	  }
      }
    }

}