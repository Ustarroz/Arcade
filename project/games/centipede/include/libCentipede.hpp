#ifndef LIBCENTIPEDE_HPP_
# define LIBCENTIPEDE_HPP_

#include "IGame.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Protocol.hpp"
#include "CentipedeGUI.hpp"

#define MAXSCORE 500
#define MINSCORE 50
#define STEPSCORE 10

namespace arcade
{
  class Centipede: public IGame
  {
   public:
      enum DirCentipede{
        DIR_UP = 0,
        DIR_LEFT,
        DIR_RIGHT,
        DIR_DOWN
      };
      struct PosCentipede{
	PosCentipede(int x, int y, DirCentipede dir, Tile const & mtile)
	{
	  _x = x;
	  _y = y;
	  _dir = dir;
	  _tile = mtile;
	};
	int		_x;
	int 		_y;
	DirCentipede	_dir;
	Tile		_tile = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
					 {0, 0, 0, 0}, 0, 0, 0, 0);
      };
      Centipede();
      virtual ~Centipede();
      virtual GameState getGameState() const;
      virtual void notifyEvent(std::vector<Event> &&events);
      virtual void notifyNetwork(std::vector<NetworkPacket> &&events);
      virtual std::vector<NetworkPacket> &&getNetworkToSend();
      virtual void process();
      virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;
      virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
      virtual std::vector<Sound> getSoundsToPlay();
      virtual IMap const &getCurrentMap() const;
      virtual IGUI &getGUI();
      virtual std::vector<Position> getPlayer() const;
    private:
      Map m_map;
      std::vector<std::pair<std::string, SoundType> > m_soundsName;
      std::vector<NetworkPacket> m_net;
      std::vector<std::unique_ptr<ISprite> > m_sprites;
      std::vector<PosCentipede> m_dir;
      size_t m_appleScore;
      size_t m_score;
      GameState m_state;
      CentipedeGUI m_gui;
      void useEvent(Event event);
      void useEventKeyBoard(Event event);
      void useEventKeyJoystick(Event event);
      void useEventKeyButton(Event event);
      void placeApple();
      void addCentipede();
      void resetGame(bool first);
      std::vector<Sound> m_soundsPlay;
  };
}

void	Play();

extern "C"
{
  arcade::IGame *getGame();
}

#endif
