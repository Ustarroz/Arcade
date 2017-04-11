#ifndef LIBSNAKE_HPP_
# define LIBSNAKE_HPP_

#include "IGame.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Protocol.hpp"
#include "GameGUI.hpp"
#include "gameCommon.hpp"

#define MAXSCORE 500
#define MINSCORE 50
#define STEPSCORE 10
#define SNAKE_EMPTY_COLOR {0, 0, 255, 0}
#define SNAKE_HIGH_FILE "score/snake_high.txt"

namespace arcade
{
  class Snake: public IGame
  {
   public:
      Snake();
      virtual ~Snake();
      virtual GameState getGameState() const;
      virtual void notifyEvent(std::vector<Event> &&events);
      virtual void notifyNetwork(std::vector<NetworkPacket> &&events);
      virtual std::vector<NetworkPacket> getNetworkToSend();
      virtual bool hasNetwork() const;
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
      std::vector<PosGame> m_dir;
      size_t m_appleScore;
      size_t m_score;
      GameState m_state;
      GameProcess m_process;
      GameGUI m_gui;
      bool m_dirSet;
      void useEvent(Event const & event);
      void useEventKeyBoard(Event const & event);
      void useEventKeyJoystick(Event const  &event);
      void useEventKeyButton(Event const &event);
      void placeApple();
      void addSnake();
      void resetGame(bool first);
      void endGame();
      std::vector<Sound> m_soundsPlay;
  };
}


extern "C"
{
  arcade::IGame *getGame();
  void	Play();
}

#endif
