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
   : m_map(40, 40)
  {
    m_map.addLayer();
    resetGame(true);
    size_t tmp = readHigh(CENTIPEDE_HIGH_FILE);
    m_gui.setHighScore(tmp);
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

    for (unsigned int x = 0; x < m_map.getWidth(); x++)
      for (unsigned int y = 0; y < m_map.getHeight(); y++)
	{
	  m_map.setTile(0, x, y, reset);
	}
    if (!first)
      {
	m_centipede.clear();
      }
    m_shoot._tile = Tile(TileType::MY_SHOOT, TileTypeEvolution::SHOT_PLAYER,
			 {0, 0, 255, 255}, 0, 0, 0, 0);
    m_shoot._dir = DirGame::DIR_DOWN;
    m_player._x = m_map.getWidth() / 2;
    m_player._y = m_map.getHeight() * 9 / 10;
    m_player._tile = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			    {255, 255, 255, 255}, 0, 0, 0, 0);
    m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
    /*posx = m_map.getWidth() / 2;
    posy = m_map.getHeight() / 2 - 1;
    m_centipede.push_back(PosGame(posx, posy, DIR_UP,
			    Tile(TileType::EMPTY,
				 TileTypeEvolution::PLAYER,
				 {255, 255, 255, 255}, 0, 0, 0, 0)));
    m_centipede.push_back(PosGame(posx, posy + 1, DIR_UP,
			    Tile(TileType::EMPTY,
				 TileTypeEvolution::OBSTACLE,
				 {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_centipede.push_back(PosGame(posx, posy + 2, DIR_UP,
			    Tile(TileType::EMPTY,
				 TileTypeEvolution::OBSTACLE,
				 {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_centipede.push_back(PosGame(posx, posy + 3, DIR_UP,
			    Tile(TileType::EMPTY,
				 TileTypeEvolution::OBSTACLE,
				 {0, 255, 0, 255}, 0, 0, 0, 0)));
    m_map.setTile(0, m_centipede[0]._x, m_centipede[0]._y, m_centipede[0]._tile);
    m_map.setTile(0, m_centipede[1]._x, m_centipede[1]._y, m_centipede[1]._tile);
    m_map.setTile(0, m_centipede[2]._x, m_centipede[2]._y, m_centipede[2]._tile);
    m_map.setTile(0, m_centipede[3]._x, m_centipede[3]._y, m_centipede[3]._tile);*/
    for (int i = 0; i < m_map.getWidth() * m_map.getHeight() / 50; i++)
      {
	randShroom();
      }
    m_score = 0;
    m_gui.setScore(0);
  }

  GameState Centipede::getGameState() const
  {
    return (m_state);
  }

  bool Centipede::checkPos(int x, int y, size_t limit_y)
  {
    return (!(y < static_cast<int>(limit_y) ||
	      y >= static_cast<int>(m_map.getHeight()) ||
	      x < 0 || x >= static_cast<int>(m_map.getWidth()) ||
	      m_map.getLayer(0).getTile(x, y).getType()
	      == TileType::OBSTACLE));
  }

  void Centipede::useEventKeyBoard(Event event)
  {
    switch (event.kb_key)
      {
	case KB_ARROW_LEFT:
	  if (checkPos(m_player._x - 1, m_player._y, m_map.getHeight() * 4 / 5))
	    {
	      m_map.setTile(0, m_player._x, m_player._y,
			    Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
				 {255, 0, 0, 255}, 0, 0, 0, 0));
	      --m_player._x;
	      m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
	    }
	break;
	case KB_ARROW_RIGHT:
	  if (checkPos(m_player._x + 1, m_player._y, m_map.getHeight() * 4 / 5))
	    {
	      m_map.setTile(0, m_player._x, m_player._y,
			    Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
				 {255, 0, 0, 255}, 0, 0, 0, 0));
	      ++m_player._x;
	      m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
	    }
	break;
	case KB_ARROW_DOWN:
	  if (checkPos(m_player._x, m_player._y + 1, m_map.getHeight() * 4 / 5))
	    {
	      m_map.setTile(0, m_player._x, m_player._y,
			    Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
				 {255, 0, 0, 255}, 0, 0, 0, 0));
	      ++m_player._y;
	      m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
	    }
	break;
	case KB_ARROW_UP:
	  if (checkPos(m_player._x, m_player._y - 1, m_map.getHeight() * 4 / 5))
	    {
	      m_map.setTile(0, m_player._x, m_player._y,
			    Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
				 {255, 0, 0, 255}, 0, 0, 0, 0));
	      --m_player._y;
	      m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
	    }
	break;
	case KB_SPACE:
	  if (m_shoot._dir == DIR_DOWN)
	    {
	      if (checkPos(m_player._x, m_player._y - 1, 0))
		{
		  m_shoot._dir = DIR_UP;
		  m_shoot._x = m_player._x;
		  m_shoot._y = m_player._y - 1;
		  m_map.setTile(0, m_shoot._x, m_shoot._y, m_shoot._tile);
		}
	      else
		shotAt(m_player._x, m_player._y - 1);
	    }
	break;
	case KB_ENTER:
	  if (m_state == GameState::INGAME)
	    {
	      m_state = GameState::MENU;
	      m_gui.setGameOver(true, "Pause");
	    }
	  else
	    {
	      if (m_state == GameState::QUIT)
		resetGame(false);
	      m_state = GameState::INGAME;
	      m_gui.setGameOver(false);
	    }
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
	useEvent(*it);
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

  void Centipede::processShoot()
  {
    bool	check_one = checkPos(m_shoot._x, m_shoot._y - 1, 0);
    bool	check_two = checkPos(m_shoot._x, m_shoot._y - 2, 0);

    m_map.setTile(0, m_shoot._x, m_shoot._y,
		  Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
		       {255, 0, 0, 255}, 0, 0, 0, 0));
    if (check_one && check_two)
      {
	m_shoot._y = m_shoot._y - 2;
	m_map.setTile(0, m_shoot._x, m_shoot._y, m_shoot._tile);
      }
    else if (check_one)
      {
	m_shoot._y = m_shoot._y - 1;
	m_map.setTile(0, m_shoot._x, m_shoot._y, m_shoot._tile);
      }
    else
      {
	if (m_shoot._y > 0)
	  shotAt(m_shoot._x, m_shoot._y);
	m_shoot._dir = DirGame::DIR_DOWN;
      }
  }

  void Centipede::process()
  {
    DirGame	save;
    DirGame	subsave;

    if (m_state != GameState::INGAME)
      return ;
    if (m_shoot._dir == DirGame::DIR_UP)
      processShoot();
    /*save = m_centipede[0]._dir;
    for(std::vector<PosGame>::iterator it = m_centipede.begin();
	it != m_centipede.end(); ++it)
      {
	m_map.setTile(0, it->_x, it->_y,
		      Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			   {255, 0, 0, 255}, 0, 0, 0, 0));
	changeDir(*it, it->_dir);
	subsave = it->_dir;
	it->_dir = save;
	save = subsave;
	if (it != m_centipede.begin())
	  m_map.setTile(0, it->_x, it->_y, it->_tile);
      }
    if (m_centipede[0]._x < 0 || m_centipede[0]._x >= static_cast<int>(m_map.getWidth()) ||
	m_centipede[0]._y < 0 || m_centipede[0]._y >= static_cast<int>(m_map.getHeight()) ||
	m_map.getLayer(0).getTile(m_centipede[0]._x, m_centipede[0]._y).getTypeEv()
	== TileTypeEvolution ::OBSTACLE)
      {
	changeDir(m_centipede[0], oppositeDir(m_centipede[0]._dir));
	m_map.setTile(0, m_centipede[0]._x, m_centipede[0]._y, m_centipede[0]._tile);
	endGame();
	return ;
      }
    if (m_map.getLayer(0).getTile(m_centipede[0]._x, m_centipede[0]._y).getTypeEv()
	== TileTypeEvolution ::FOOD)
      {
	m_score = m_score + m_appleScore;
	m_map.setTile(0, m_centipede[0]._x, m_centipede[0]._y, m_centipede[0]._tile);
	m_gui.setScore(m_score);
	addCentipede();
	addShroom();
      }
    else
      {
	if (m_appleScore >= MINSCORE + STEPSCORE)
	  m_appleScore = m_appleScore - STEPSCORE;
	m_map.setTile(0, m_centipede[0]._x, m_centipede[0]._y, m_centipede[0]._tile);
      }*/
  }

  void Centipede::addShroom(int x, int y)
  {
    Shroom shroom;

    shroom._pos.x = x;
    shroom._pos.y = y;
    shroom._life = 5;
    shroom._tile = Tile(TileType::OBSTACLE, TileTypeEvolution::OBSTACLE,
			{255, 0, 0, 255}, 0, 0, 0, 0);
    m_shroom.push_back(shroom);
    m_map.setTile(0, shroom._pos.x, shroom._pos.y, shroom._tile);
  }

  void Centipede::randShroom()
  {
    std::vector<size_t> list;
    size_t pos;

    for (std::size_t x = 0; x != m_map.getWidth(); x++)
      {
	for (std::size_t y = 0; y < m_map.getHeight() - 1; y++)
	  if (m_map.getLayer(0).getTile(x, y).getTypeEv()
	      == TileTypeEvolution::EMPTY &&
	   (static_cast<int>(x) != m_player._x ||
	    static_cast<int>(y) != !m_player._y))
	    list.push_back(x + y * m_map.getWidth());
      }
    if (list.size() == 0)
      return ;
    pos = list[std::rand() % list.size()];
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
	PosGame tail = m_centipede.back();
	if (tmp != tail._dir)
	  {
	    changeDir(tail, static_cast<DirGame>(tmp));
	    tail._dir = oppositeDir(static_cast<DirGame>(tmp));
	    if (tail._x < 0 || tail._x >= static_cast<int>(m_map.getWidth()) ||
		tail._y < 0 || tail._y >= static_cast<int>(m_map.getHeight()))
	      {
		tmp = tmp + 1;
		continue ;
	      }
	    loop = false;
	    for (std::vector<PosGame>::iterator it = m_centipede.begin();
		 it != m_centipede.end(); ++it)
	      if (it->_x == tail._x && it->_y == tail._y)
		{
		  loop = true;
		}
	  }
	if (!loop)
	  m_centipede.push_back(tail);
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

    for(std::vector<PosGame>::const_iterator it = m_centipede.begin();
	it != m_centipede.end(); ++it)
      {
	Position pos;
	pos.x = static_cast<uint16_t >(it->_x);
	pos.y = static_cast<uint16_t >(it->_y);
	list.push_back(pos);
      }
    return (list);
  }

  void Centipede::endGame()
  {
    size_t tmp = readHigh(CENTIPEDE_HIGH_FILE);
    if (tmp >= m_score)
      m_gui.setHighScore(tmp);
    else
      {
	writeHigh( CENTIPEDE_HIGH_FILE, m_score);
	m_gui.setHighScore(m_score);
      }
    m_state = GameState::QUIT;
    m_gui.setGameOver(true, "Game Over");
  }

  void Centipede::shotShroom(int x, int y)
  {
    for (std::vector<Shroom>::iterator it = m_shroom.begin();
	 it != m_shroom.end(); it++)
      {
	if (it->_pos.x == x && it->_pos.y == y)
	  {
	    --it->_life;
	    if (it->_life == 0)
	      {
		m_map.setTile(0, it->_pos.x, it->_pos.y,
			      Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
				   {255, 0, 0, 255}, 0, 0, 0, 0));
		m_shroom.erase(it);
		m_score = m_score + SHROOM_SCORE;
	      }
	    else
	      m_map.setTile(0, it->_pos.x, it->_pos.y,
			    Tile(TileType::OBSTACLE, TileTypeEvolution::OBSTACLE,
				 {static_cast<uint8_t >(50 * it->_life), 0, 0, 255}, 0, 0, 0, 0));
	  }
      }
  }

  void Centipede::shotAt(int x, int y)
  {
    if (m_map.getLayer(0).getTile(x, y).getTypeEv()
	== TileTypeEvolution::OBSTACLE)
      shotShroom(x, y);
  }
}

extern "C"
{
arcade::IGame *getGame()
{
  return (new arcade::Centipede());
}
}
