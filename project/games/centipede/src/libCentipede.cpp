#include <algorithm>
#include <string>
#include "libCentipede.hpp"
#include "Map.hpp"
#include "GameState.hpp"
#include "Tile.hpp"

#include <iostream>
namespace arcade
{
  Centipede::Centipede()
    : m_map(64, 40)
  {
    m_map.addLayer();
    resetGame(true);
    m_state = GameState::INGAME;
  }

  Centipede::~Centipede()
  {
  }

  void Centipede::resetGame(bool first)
  {
    Tile reset = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
    		{255, 0, 0, 255}, 0, 0, 0, 0);
    size_t posx;
    size_t posy;

    if (!first)
      {
	for (std::vector<PosCentipede>::iterator it = m_dir.begin();
	     it != m_dir.end(); ++it)
	  {
	    m_map.setTile(0, it->_x, it->_y, reset);
	  }
	for (unsigned int x = 0; x < m_map.getWidth(); x++)
	    for (unsigned int y = 0; y < m_map.getHeight(); y++)
	      if (m_map.getLayer(0).getTile(x, y).getTypeEv() ==
		 TileTypeEvolution::FOOD)
		{
		  m_map.setTile(0, x, y, reset);
		  x = m_map.getWidth();
		  y = m_map.getHeight();
		}
	m_dir.clear();
      }
    posx = m_map.getWidth() / 2;
    posy = m_map.getHeight() / 2 - 1;
    m_dir.push_back(PosCentipede(posx, posy, DIR_UP,
			     Tile(TileType::OTHER,
				  TileTypeEvolution::PLAYER,
				  {255, 255, 255, 255}, 0, 0, 0, 0)));
    m_dir.push_back(PosCentipede(posx, posy + 1, DIR_UP,
			     Tile(TileType::OBSTACLE,
				  TileTypeEvolution::OBSTACLE,
				  {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_dir.push_back(PosCentipede(posx, posy + 2, DIR_UP,
			     Tile(TileType::OBSTACLE,
				  TileTypeEvolution::OBSTACLE,
				  {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
    m_map.setTile(0, m_dir[1]._x, m_dir[1]._y, m_dir[1]._tile);
    m_map.setTile(0, m_dir[2]._x, m_dir[2]._y, m_dir[2]._tile);
    placeApple();
    m_score = 0;
  }

  GameState Centipede::getGameState() const
  {
    return (m_state);
  }

  void Centipede::useEventKeyBoard(Event event)
  {
    switch (event.kb_key)
    {
	case KB_ARROW_LEFT:
	  m_dir[0]._dir = m_dir[0]._dir != DIR_RIGHT ? DIR_LEFT : DIR_RIGHT;
	  break;
	case KB_ARROW_RIGHT:
	  m_dir[0]._dir = m_dir[0]._dir == DIR_LEFT ? DIR_LEFT : DIR_RIGHT;
	  break;
	case KB_ARROW_DOWN:
	  m_dir[0]._dir = m_dir[0]._dir == DIR_UP ? DIR_UP : DIR_DOWN;
	  break;
	case KB_ARROW_UP:
	  m_dir[0]._dir = m_dir[0]._dir != DIR_DOWN ? DIR_UP : DIR_DOWN;
	  break;
	case KB_ENTER:
	  m_state = GameState::MENU;
	  return ;
	default:
	  break;
    }
  }

  void Centipede::useEventKeyButton(Event event)
  {
    (void)event;
  }

  void Centipede::useEventKeyJoystick(Event event)
  {
    (void)event;
  }

  void Centipede::useEvent(Event event)
  {
    switch (event.type)
      {
	case ET_KEYBOARD:
	  useEventKeyBoard(event);
	  break;
	case ET_JOYSTICK:
	  useEventKeyJoystick(event);
	  break;
	case ET_BUTTON:
	  useEventKeyButton(event);
	  break;
	default:
	  break;
      }
  }

  void Centipede::notifyEvent(std::vector<Event> &&event)
  {
    for(std::vector<Event>::iterator it = event.begin();
	it != event.end(); ++it)
      {
	if (m_state == GameState::INGAME)
	  useEvent(*it);
	else
	  {
	    GameState prev;

	    prev = m_state;
	    m_state = m_gui.useEventGUI(*it, m_state);
	    if (prev == GameState::QUIT && m_state == INGAME)
	      resetGame(false);
	  }
      }
  }

  void Centipede::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
    (void)events;
  }

  std::vector<NetworkPacket> &&Centipede::getNetworkToSend()
  {
    return (std::move(m_net));
  }

  static Centipede::DirCentipede oppositeDir(Centipede::DirCentipede dir)
  {
    switch (dir)
      {
	case Centipede::DIR_UP:
	  return (Centipede::DIR_DOWN);
	case Centipede::DIR_DOWN:
	  return (Centipede::DIR_UP);
	case Centipede::DIR_LEFT:
	  return (Centipede::DIR_RIGHT);
	case Centipede::DIR_RIGHT:
	  return (Centipede::DIR_LEFT);
        default:
          return (Centipede::DIR_UP);
      }
  }

  static void changeDir(Centipede::PosCentipede &cpy, Centipede::DirCentipede dir)
  {
    switch (dir)
      {
	case Centipede::DIR_RIGHT :
	  cpy._x = cpy._x + 1;
	  break;
	case Centipede::DIR_LEFT :
	  cpy._x = cpy._x - 1;
	  break;
	case Centipede::DIR_UP :
	  cpy._y = cpy._y - 1;
	  break;
	case Centipede::DIR_DOWN :
	  cpy._y = cpy._y + 1;
	  break;
      }
  }

  void Centipede::process()
  {
    DirCentipede	save;
    DirCentipede	subsave;

    if (m_state != GameState::INGAME)
      return ;
    save = m_dir[0]._dir;
    for(std::vector<PosCentipede>::iterator it = m_dir.begin();
	it != m_dir.end(); ++it)
      {
	m_map.setTile(0, it->_x, it->_y,
		      Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			   {255, 0, 0, 255}, 0, 0, 0, 0));
	changeDir(*it, it->_dir);
	subsave = it->_dir;
	it->_dir = save;
	save = subsave;
	if (it != m_dir.begin())
	  m_map.setTile(0, it->_x, it->_y, it->_tile);
      }
    if (m_dir[0]._x < 0 || m_dir[0]._x >= static_cast<int>(m_map.getWidth()) ||
     	m_dir[0]._y < 0 || m_dir[0]._y >= static_cast<int>(m_map.getHeight()) ||
     	m_map.getLayer(0).getTile(m_dir[0]._x, m_dir[0]._y).getType()
     	== TileType::OBSTACLE)
      {
	changeDir(m_dir[0], oppositeDir(m_dir[0]._dir));
	m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
	std::cout << "score " << m_score << std::endl;
	m_state = GameState::QUIT;
	return ;
      }
    if (m_map.getLayer(0).getTile(m_dir[0]._x, m_dir[0]._y).getTypeEv()
	== TileTypeEvolution ::FOOD)
      {
	m_score = m_score + m_appleScore;
	m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
	m_gui.setScore(m_score);
	addCentipede();
	placeApple();
      }
    else
      {
	if (m_appleScore >= MINSCORE + STEPSCORE)
	  m_appleScore = m_appleScore - STEPSCORE;
	m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
      }
  }

  void Centipede::placeApple()
  {
    std::vector<size_t> list;
    size_t pos;

    for (std::size_t x = 0; x != m_map.getWidth(); x++)
      {
	for (std::size_t y = 0; y != m_map.getHeight(); y++)
	  {
	    list.push_back(x + y * m_map.getWidth());
	  }
      }
    for (std::vector<PosCentipede>::iterator it = m_dir.begin();
	 it != m_dir.end(); it++)
      {
	list.erase(std::find(list.begin(), list.end(), it->_x + it->_y * m_map.getWidth()));
      }
    if (list.size() == 0)
      {
	std::cout << "score " << m_score << std::endl;
	m_state = GameState::QUIT;
	return ;
      }
    pos = list[std::rand() % list.size()];
    m_appleScore = MAXSCORE;
    m_map.setTile(0, pos % m_map.getWidth(), pos / m_map.getWidth(),
		  Tile(TileType::POWERUP, TileTypeEvolution::FOOD,
		       {255, 0, 255, 255}, 0, 0, 0, 0));
  }

  void Centipede::addCentipede()
  {
    int tmp;
    bool loop;

    tmp = DIR_UP;
    loop = true;
    while (tmp <= DIR_DOWN && loop)
      {
	PosCentipede tail = m_dir.back();
	if (tmp != tail._dir)
	  {
	    changeDir(tail, static_cast<DirCentipede>(tmp));
	    tail._dir = oppositeDir(static_cast<DirCentipede>(tmp));
	    if (tail._x < 0 || tail._x >= static_cast<int>(m_map.getWidth()) ||
		tail._y < 0 || tail._y >= static_cast<int>(m_map.getHeight()))
	      {
		tmp = tmp + 1;
		continue ;
	      }
	    loop = false;
	    for (std::vector<PosCentipede>::iterator it = m_dir.begin();
		 it != m_dir.end(); ++it)
	      if (it->_x == tail._x && it->_y == tail._y)
		{
		  loop = true;
		}
	  }
	if (!loop)
	  m_dir.push_back(tail);
	tmp = tmp + 1;
      }
    if (loop)
      resetGame(false);
  }

  std::vector<std::unique_ptr<ISprite>> Centipede::getSpritesToLoad() const
  {
    std::vector<std::unique_ptr<ISprite> > sprites;
    return (std::move(sprites));
  }

  std::vector<std::pair<std::string, SoundType> > Centipede::getSoundsToLoad() const
  {
    return (std::move(m_soundsName));
  }

  std::vector<Sound> Centipede::getSoundsToPlay()
  {
    return (std::move(m_soundsPlay));
  }

  IMap const &Centipede::getCurrentMap() const
  {
    return (m_map);
  }

  IGUI &Centipede::getGUI()
  {
    return (m_gui);
  }

  std::vector<Position> Centipede::getPlayer() const
  {
    std::vector<Position> list;

    for(std::vector<PosCentipede>::const_iterator it = m_dir.begin();
     	it != m_dir.end(); ++it)
      {
	Position pos;
	pos.x = static_cast<uint16_t >(it->_x);
	pos.y = static_cast<uint16_t >(it->_y);
	list.push_back(pos);
      }
    return (list);
  }
}

extern "C"
{
  arcade::IGame *getGame()
  {
    return (new arcade::Centipede());
  }
}
