#include <algorithm>
#include <string>
#include "libSnake.hpp"
#include "Map.hpp"
#include "GameState.hpp"
#include "Tile.hpp"

#include <iostream>
namespace arcade
{
  Snake::Snake()
    : m_map(64, 40)
  {
    m_map.addLayer();
    resetGame(true);
    m_state = GameState::INGAME;
  }

  Snake::~Snake()
  {
  }

  void Snake::resetGame(bool first)
  {
    Tile reset = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
    		{255, 0, 0, 255}, 0, 0, 0, 0);
    size_t posx;
    size_t posy;

    if (!first)
      {
	std::cout << "score " << m_score << std::endl;
	for (std::vector<PosSnake>::iterator it = m_dir.begin();
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
    m_dir.push_back(PosSnake(posx, posy, DIR_UP,
			     Tile(TileType::OTHER,
				  TileTypeEvolution::PLAYER,
				  {0, 0, 255, 255}, 0, 0, 0, 0)));
    m_dir.push_back(PosSnake(posx, posy + 1, DIR_UP,
			     Tile(TileType::OBSTACLE,
				  TileTypeEvolution::OBSTACLE,
				  {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_dir.push_back(PosSnake(posx, posy + 2, DIR_UP,
			     Tile(TileType::OBSTACLE,
				  TileTypeEvolution::OBSTACLE,
				  {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
    m_map.setTile(0, m_dir[1]._x, m_dir[1]._y, m_dir[1]._tile);
    m_map.setTile(0, m_dir[2]._x, m_dir[2]._y, m_dir[2]._tile);
    placeApple();
    m_score = 0;
    m_state = GameState::QUIT;
  }

  GameState Snake::getGameState() const
  {
    return (m_state);
  }

  void Snake::useEventKeyBoard(Event event)
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

  void Snake::useEventKeyButton(Event event)
  {
    (void)event;
  }

  void Snake::useEventKeyJoystick(Event event)
  {
    (void)event;
  }

  void Snake::useEvent(Event event)
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

  void Snake::notifyEvent(std::vector<Event> &&event)
  {
    for(std::vector<Event>::iterator it = event.begin();
	it != event.end(); ++it)
      {
	if (m_state == GameState::INGAME)
	  useEvent(*it);
	else
	  m_state = m_gui.useEventGUI(*it, m_state);
      }
  }

  void Snake::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
    (void)events;
  }

  std::vector<NetworkPacket> &&Snake::getNetworkToSend()
  {
    return (std::move(m_net));
  }

  static Snake::DirSnake oppositeDir(Snake::DirSnake dir)
  {
    switch (dir)
      {
	case Snake::DIR_UP:
	  return (Snake::DIR_DOWN);
	case Snake::DIR_DOWN:
	  return (Snake::DIR_UP);
	case Snake::DIR_LEFT:
	  return (Snake::DIR_RIGHT);
	case Snake::DIR_RIGHT:
	  return (Snake::DIR_LEFT);
        default:
          return (Snake::DIR_UP);
      }
  }

  static void changeDir(Snake::PosSnake &cpy, Snake::DirSnake dir)
  {
    switch (dir)
      {
	case Snake::DIR_RIGHT :
	  cpy._x = cpy._x + 1;
	  break;
	case Snake::DIR_LEFT :
	  cpy._x = cpy._x - 1;
	  break;
	case Snake::DIR_UP :
	  cpy._y = cpy._y - 1;
	  break;
	case Snake::DIR_DOWN :
	  cpy._y = cpy._y + 1;
	  break;
      }
  }

  void Snake::process()
  {
    DirSnake	save;
    DirSnake	subsave;

    if (m_state != GameState::INGAME)
      return ;
    save = m_dir[0]._dir;
    for(std::vector<PosSnake>::iterator it = m_dir.begin();
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
	resetGame(false);
	return ;
      }
    if (m_map.getLayer(0).getTile(m_dir[0]._x, m_dir[0]._y).getTypeEv()
	== TileTypeEvolution ::FOOD)
      {
	m_score = m_score + m_appleScore;
	m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
	m_gui.setScore(m_score);
	addSnake();
	placeApple();
      }
    else
      {
	if (m_appleScore >= MINSCORE + STEPSCORE)
	  m_appleScore = m_appleScore - STEPSCORE;
	m_map.setTile(0, m_dir[0]._x, m_dir[0]._y, m_dir[0]._tile);
      }
  }

  void Snake::placeApple()
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
    for (std::vector<PosSnake>::iterator it = m_dir.begin();
	 it != m_dir.end(); it++)
      {
	list.erase(std::find(list.begin(), list.end(), it->_x + it->_y * m_map.getWidth()));
      }
    if (list.size() == 0)
      {
	resetGame(false);
	return ;
      }
    pos = list[std::rand() % list.size()];
    m_appleScore = MAXSCORE;
    m_map.setTile(0, pos % m_map.getWidth(), pos / m_map.getWidth(),
		  Tile(TileType::POWERUP, TileTypeEvolution::FOOD,
		       {255, 0, 255, 255}, 0, 0, 0, 0));
  }

  void Snake::addSnake()
  {
    int tmp;
    bool loop;

    tmp = DIR_UP;
    loop = true;
    while (tmp <= DIR_DOWN && loop)
      {
	PosSnake tail = m_dir.back();
	if (tmp != tail._dir)
	  {
	    changeDir(tail, static_cast<DirSnake>(tmp));
	    tail._dir = oppositeDir(static_cast<DirSnake>(tmp));
	    if (tail._x < 0 || tail._x >= static_cast<int>(m_map.getWidth()) ||
		tail._y < 0 || tail._y >= static_cast<int>(m_map.getHeight()))
	      {
		tmp = tmp + 1;
		continue ;
	      }
	    loop = false;
	    for (std::vector<PosSnake>::iterator it = m_dir.begin();
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

  std::vector<std::unique_ptr<ISprite>> Snake::getSpritesToLoad() const
  {
    std::vector<std::unique_ptr<ISprite> > sprites;
    return (std::move(sprites));
  }

  std::vector<std::pair<std::string, SoundType> > Snake::getSoundsToLoad() const
  {
    return (std::move(m_soundsName));
  }

  std::vector<Sound> Snake::getSoundsToPlay()
  {
    return (std::move(m_soundsPlay));
  }

  IMap const &Snake::getCurrentMap() const
  {
    return (m_map);
  }

  IGUI &Snake::getGUI()
  {
    return (m_gui);
  }

  std::vector<Position> Snake::getPlayer() const
  {
    std::vector<Position> list;

    for(std::vector<PosSnake>::const_iterator it = m_dir.begin();
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
    return (new arcade::Snake());
  }
}
