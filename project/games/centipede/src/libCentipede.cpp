#include <algorithm>
#include <string>
#include "libCentipede.hpp"
#include "Map.hpp"
#include "GameState.hpp"
#include "Tile.hpp"

#include <iostream>
#include <unistd.h>
namespace arcade
{
  Centipede::Centipede()
   : m_map(15, 15)
  {
    m_level = CENTIPEDE_MIN_LVL;
    size_t tmp = readHigh(CENTIPEDE_HIGH_FILE);
    m_gui.setHighScore(tmp);
    m_state = GameState::INGAME;
    m_process = GameProcess::GAMEPLAYING;
    m_map.addLayer();
    resetGame(true);
  }

  Centipede::~Centipede()
  {
  }

  void Centipede::addCentipede()
  {
    DirGame dir;
    int posx;
    int posy = 0;

    dir = rand() % 2 == 0 ? DIR_RIGHT : DIR_LEFT;
    if (dir == DIR_RIGHT)
      posx = m_map.getWidth() * m_level / CENTIPEDE_MAX_LVL;
    else
      posx = m_map.getWidth() * (CENTIPEDE_MAX_LVL - m_level) / CENTIPEDE_MAX_LVL;
    std::vector<CentiPart> list;
    for (int x = posx;
	 dir == DIR_RIGHT ? x >= 0 : x < static_cast<int>(m_map.getWidth());
	 dir == DIR_RIGHT ? --x : ++x)
      {
	PosGame pos = (PosGame(x, posy, dir,
			       Tile(TileType::EVIL_DUDE,
				    TileTypeEvolution::ENEMY,
				    CENTIPEDE_PART_COLOR,
				    0, 0, 0, 0)));
	list.push_back(CentiPart(pos, dir));
	m_map.setTile(0, pos._x, pos._y, pos._tile);
      }
    m_centipede.push_back(list);
  }

  void Centipede::resetGame(bool first)
  {
    Tile reset = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
		      CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0);
    for (unsigned int x = 0; x < m_map.getWidth(); x++)
      for (unsigned int y = 0; y < m_map.getHeight(); y++)
	{
	  m_map.setTile(0, x, y, reset);
	}
    if (!first)
      {
	m_centipede.clear();
	m_shroom.clear();
      }
    m_shoot._tile = Tile(TileType::MY_SHOOT, TileTypeEvolution::SHOT_PLAYER,
			 {0, 0, 255, 255}, 0, 0, 0, 0);
    m_shoot._dir = DirGame::DIR_DOWN;
    m_player._x = m_map.getWidth() / 2;
    m_player._y = m_map.getHeight() * 9 / 10;
    m_player._tile = Tile(TileType::EMPTY, TileTypeEvolution::PLAYER,
			    {205, 205, 205, 255}, 0, 0, 0, 0);
    m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
    addCentipede();
    for (size_t i = 0; i < m_map.getWidth() * m_map.getHeight() / 50; i++)
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

  TileType Centipede::checkPos(int x, int y, size_t limit_y)
  {
    if (y < static_cast<int>(limit_y) ||
	  y >= static_cast<int>(m_map.getHeight()) ||
	  x < 0 || x >= static_cast<int>(m_map.getWidth()))
      return (TileType::OTHER);
    if (m_map.getLayer(0).getTile(x, y).getTypeEv()
	== TileTypeEvolution::OBSTACLE)
      return (TileType::OBSTACLE);
    if (m_map.getLayer(0).getTile(x, y).getTypeEv()
	== TileTypeEvolution::ENEMY)
      return (TileType::EVIL_DUDE);
    if (m_map.getLayer(0).getTile(x, y).getTypeEv()
	== TileTypeEvolution::SHOT_PLAYER)
      return (TileType::MY_SHOOT);
    return (TileType::EMPTY);
  }

  void Centipede::useEventKeyBoard(Event event)
  {
    int x;
    int y;
    TileType type;

    switch (event.kb_key)
      {
	case KB_ARROW_LEFT:
	  {
	    x = m_player._x - 1;
	    y = m_player._y;
	    break;
	  }
	case KB_ARROW_RIGHT:
	  {
	    x = m_player._x + 1;
	    y = m_player._y;
	    break;
	  }
	case KB_ARROW_DOWN:
	  {
	    x = m_player._x;
	    y = m_player._y + 1;
	    break;
	  }
	case KB_ARROW_UP:
	  {
	    x = m_player._x;
	    y = m_player._y - 1;
	    break;
	  }
	case KB_SPACE:
	  if (m_process == GameProcess::GAMEPLAYING && m_shoot._dir == DIR_DOWN)
	    {
	      type = checkPos(m_player._x, m_player._y - 1, 0);
	      if (type == TileType::EMPTY)
		{
		  m_shoot._dir = DIR_UP;
		  m_shoot._x = m_player._x;
		  m_shoot._y = m_player._y;
		}
	      else if (type != TileType::OTHER && type != TileType::MY_SHOOT)
		{
		  shotAt(m_player._x, m_player._y - 1);
		}
	    }
	return ;
	case KB_ENTER:
	  if (m_process == GameProcess::GAMEPLAYING)
	    {
	      m_process = GameProcess::GAMEPAUSE;
	      m_gui.setGameOver(true, "Pause");
	    }
	  else
	    {
	      if (m_process == GameProcess::GAMEOVER)
		resetGame(false);
	      m_process = GameProcess::GAMEPLAYING;
	      m_gui.setGameOver(false);
	    }
	return ;
	case KB_9:
	  endGame();
	  m_state = GameState::MENU;
	return ;
	case KB_8:
	  endGame();
	  resetGame(false);
	  m_process = GameProcess::GAMEPLAYING;
	  m_gui.setGameOver(false);
	return ;
	case KB_ESCAPE:
	  endGame();
	  m_state = GameState::QUIT;
	return ;
	default:
	  return ;
      }
    if (m_process != GameProcess::GAMEPLAYING)
      return ;
    type = checkPos(x, y, m_map.getHeight() * 4 / 5);
    if (type == TileType::EMPTY)
      {
	m_map.setTile(0, m_player._x, m_player._y,
		      Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			   CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0));
	m_player._y = y;
	m_player._x = x;
	m_map.setTile(0, m_player._x, m_player._y, m_player._tile);
      }
    else if (type == TileType::EVIL_DUDE)
      endGame();
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
	case ET_QUIT:
	  endGame();
	  m_state = GameState::QUIT;
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

  std::vector<NetworkPacket> Centipede::getNetworkToSend()
  {
    return (std::move(m_net));
  }

  bool Centipede::hasNetwork() const
  {
    return (false);
  }

  void Centipede::processShoot()
  {
    TileType	check_one = checkPos(m_shoot._x, m_shoot._y - 1, 0);
    TileType	check_two = checkPos(m_shoot._x, m_shoot._y - 2, 0);

    if (m_shoot._y != m_player._y)
    	m_map.setTile(0, m_shoot._x, m_shoot._y,
		      Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			   CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0));
    if (check_one == TileType::EMPTY && check_two == TileType::EMPTY)
      {
	m_shoot._y = m_shoot._y - 2;
	m_map.setTile(0, m_shoot._x, m_shoot._y, m_shoot._tile);
      }
    else if (check_one != TileType::OTHER && check_one != TileType::EMPTY)
      {
	shotAt(m_shoot._x, m_shoot._y - 1);
      }
    else if (check_two != TileType::OTHER && check_two != TileType::EMPTY)
      {
	shotAt(m_shoot._x, m_shoot._y - 2);
      }
    else if (check_one == TileType::EMPTY)
      {
	m_shoot._y = m_shoot._y - 1;
	m_map.setTile(0, m_shoot._x, m_shoot._y, m_shoot._tile);
      }
    else
      m_shoot._dir = DirGame::DIR_DOWN;
  }

  int Centipede::checkHead(std::vector<CentiPart> &body)
  {
    TileType check;
    PosGame pos;

    if (body.size() == 0)
      return (1);
    pos._x = body.begin()->_pos._x;
    pos._y = body.begin()->_pos._y;
    pos._dir = body.begin()->_pos._dir;
    changeDir(pos, pos._dir);
    check = checkPos(pos._x, pos._y, 0);
    if (check == TileType::MY_SHOOT)
      {
	int exit;

	exit = -3;
	if ((body.size() == 1 && m_centipede.size() == 1) ||
	    (body.size() == 1 &&
	     body[0]._pos._x == (*(m_centipede.end() - 1))[0]._pos._x))
	  exit = -1;
	else if (body.size() == 1)
	  exit = -2;
	m_map.setTile(0, body.begin()->_pos._x, body.begin()->_pos._y,
		      Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			   CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0));
	changeDir(body.begin()->_pos, body.begin()->_pos._dir);
	m_map.setTile(0, pos._x, pos._y, body.begin()->_pos._tile);
	shotAt(body.begin()->_pos._x, body.begin()->_pos._y);
	if (exit == -3)
	  return (checkHead(body));
	return (exit);
      }
    else if (pos._x == m_player._x && pos._y == m_player._y)
      {
	endGame();
	return (-1);
      }
    else if (check == TileType::EMPTY || pos._dir == DirGame::DIR_DOWN)
      return (0);
    else if (pos._y < static_cast<int>(m_map.getHeight() - 1))
      {
	body.begin()->_pos._dir = DirGame::DIR_DOWN;
	return (checkHead(body));
      }
    m_map.setTile(0, body.begin()->_pos._x, body.begin()->_pos._y,
		  Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
		       CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0));
    body.erase(body.begin());
    m_score = m_score >= SHROOM_SCORE ? m_score - SHROOM_SCORE : 0;
    m_gui.setScore(m_score);
    return (checkHead(body));
  }

  void Centipede::processCentipede()
  {
    DirGame	save;
    int		check;

    for (std::vector<std::vector<CentiPart>>::iterator it = m_centipede.begin();
	 it != m_centipede.end(); it++)
      {
	check = checkHead(*it);
	if (check == 1)
	  {
	    check = 0;
	    if (it + 1 == m_centipede.end())
	      check = 1;
	    m_centipede.erase(it);
	    if (m_centipede.size() == 0)
	      {
		addCentipede();
		check = 1;
	      }
	    if (check == 1)
	      return ;
	    continue;
	  }
	else if (check == -1)
	  return ;
	else if (check == -2)
	  continue ;
	save = it->begin()->_pos._dir;
	for (std::vector<CentiPart>::iterator jt = it->begin();
	     jt != it->end(); jt++)
	  {
	    m_map.setTile(0, jt->_pos._x, jt->_pos._y,
			  Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			       CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0));
	    changeDir(jt->_pos, jt->_pos._dir);
	    if (jt->_pos._dir == DIR_DOWN && jt == it->begin())
	      {
		save = jt->_pos._dir;
		jt->_pos._dir = oppositeDir(jt->_old_dir);
		jt->_old_dir =	jt->_pos._dir;
	      }
	    else if (jt->_pos._dir == DIR_DOWN)
	      {
		jt->_pos._dir = save;
		if (save != DIR_DOWN)
		  jt->_old_dir = jt->_pos._dir;
		save = DIR_DOWN;
	      }
	    else
	      {
		jt->_pos._dir = save;
		save = jt->_old_dir;
	      }
	    m_map.setTile(0, jt->_pos._x, jt->_pos._y, jt->_pos._tile);
	  }
      }
  }

  void Centipede::process()
  {
    if (m_process != GameProcess::GAMEPLAYING)
      return ;
    if (m_shoot._dir == DirGame::DIR_UP)
      {
	processShoot();
      }
    processCentipede();
  }

  void Centipede::addShroom(int x, int y)
  {
    Shroom shroom;

    shroom._pos.x = x;
    shroom._pos.y = y;
    shroom._life = 5;
    shroom._tile = Tile(TileType::OBSTACLE, TileTypeEvolution::OBSTACLE,
			{0, 255, 0, 255}, 0, 0, 0, 0);
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
    addShroom(pos % m_map.getWidth(), pos / m_map.getWidth());
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

  Position Centipede::getPlayer() const
  {
    Position pos;

    pos.x = m_player._x;
    pos.y = m_player._y;
    return (pos);
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
    m_process = GameProcess::GAMEOVER;
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
				   CENTIPEDE_EMPTY_COLOR, 0, 0, 0, 0));
		m_shroom.erase(it);
		m_score = m_score + SHROOM_SCORE;
		m_gui.setScore(m_score);
	      }
	    else
	      {
		uint8_t col = static_cast<uint8_t >(255 - 50 * it->_life);
		m_map.setTile(0, it->_pos.x, it->_pos.y,
			      Tile(TileType::OBSTACLE, TileTypeEvolution::OBSTACLE,
				   {col, static_cast<uint8_t >(255 - col), col, 255}, 0, 0, 0, 0));
	      }
	    return ;
	  }
      }
  }

  void	Centipede::shotCentipede(int x, int y)
  {
    for (std::vector<std::vector<CentiPart>>::iterator it = m_centipede.begin();
	 it != m_centipede.end(); it++)
      {
	for (std::vector<CentiPart>::iterator jt = it->begin();
	     jt != it->end(); jt++)
	  if (jt->_pos._x == x && jt->_pos._y == y)
	    {
	      addShroom(jt->_pos._x, jt->_pos._y);
	      	if (jt == it->begin() || (jt->_pos._x == it->back()._pos._x &&
					  jt->_pos._y == it->back()._pos._y))
		  {
		    it->erase(jt);
		    m_score = m_score + CENTIPEDE_SCORE;
		    if (it->size() == 0)
		      {
			m_centipede.erase(it);
			if (m_centipede.size() == 0)
			  {
			    m_score = m_score + CENTIPEDE_SCORE * m_level;
			    if (m_level < CENTIPEDE_MAX_LVL - 1)
			      ++m_level;
			    addCentipede();
			  }
		      }
		    m_gui.setScore(m_score);
		    return ;
		  }
		else
		  {
		    std::vector<CentiPart> list_one(it->begin(), jt);
		    std::vector<CentiPart> list_two(jt + 1, it->end());
		    it->erase(jt);
		    m_centipede.erase(it);
		    m_centipede.push_back(list_one);
		    m_centipede.push_back(list_two);
		    m_score = m_score + CENTIPEDE_SCORE;
		    m_gui.setScore(m_score);
		    return ;
		  }
	    }
      }
  }

  void Centipede::shotAt(int x, int y)
  {
    if (m_map.getLayer(0).getTile(x, y).getTypeEv()
	== TileTypeEvolution::OBSTACLE)
      shotShroom(x, y);
    else
      {
	shotCentipede(x, y);
      }
    m_shoot._dir = DirGame::DIR_DOWN;
    m_shoot._y = -1;
    m_shoot._x = -1;
  }
}

extern "C"
{
arcade::IGame *getGame()
{
  return (new arcade::Centipede());
}
}
