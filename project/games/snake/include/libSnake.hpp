#ifndef LIBSNAKE_HPP_
# define LIBSNAKE_HPP_

# include "IGame.hpp"
# include "Map.hpp"
# include "GUI.hpp"

#define MAXSCORE 100
#define MINSCORE 20
#define STEPSCORE 10

namespace arcade
{
  class Snake: public IGame
  {
   public:
      enum DirSnake{
        DIR_UP = 0,
        DIR_LEFT,
        DIR_RIGHT,
        DIR_DOWN
      };
      struct PosSnake{
	PosSnake(int x, int y, DirSnake dir, Tile const & mtile)
	{
	  _x = x;
	  _y = y;
	  _dir = dir;
	  _tile = mtile;
	};
	int		_x;
	int 		_y;
	DirSnake	_dir;
	Tile		_tile = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
					 {0, 0, 0, 0}, 0, 0, 0, 0);
      };
      struct Apple{
	int	_x;
	int	_y;
	int 	score;
      };
      Snake();
      virtual ~Snake();
      virtual GameState getGameState() const;
      virtual void notifyEvent(std::vector<Event> &&events);
      virtual void notifyNetwork(std::vector<NetworkPacket> &&events);
      virtual std::vector<NetworkPacket> &&getNetworkToSend();
      virtual void process();
      virtual std::vector<std::unique_ptr<ISprite>> &&getSpritesToLoad() const;
      virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
      virtual std::vector<int>       &&getSoundsToPlay();
      virtual IMap const &getCurrentMap() const;
      virtual IGUI &getGUI();
    private:
      Map m_map;
      GUI m_gui;
      std::vector<std::pair<std::string, SoundType> > m_soundsName;
      std::vector<NetworkPacket> m_net;
      std::vector<std::unique_ptr<ISprite> > m_sprites;
      std::vector<int> m_soundsPlay;
      std::vector<PosSnake> m_dir;
      Apple m_apple;
      size_t m_score;
      void useEvent(Event event);
      void useEventKeyBoard(Event event);
      void useEventKeyJoystick(Event event);
      void useEventKeyButton(Event event);
      void placeApple();
      void resetGame(bool first);
  };
}

extern "C"
{
  arcade::IGame *getGame();
}

#endif
