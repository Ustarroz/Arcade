#ifndef LIBSNAKE_HPP_
# define LIBSNAKE_HPP_

# include "IGame.hpp"
# include "Map.hpp"
# include "GUI.hpp"

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
      virtual std::vector<NetworkPacket> &&getNetworkToSend();
      virtual void process();
      virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;
      virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
      virtual std::vector<Sound> getSoundsToPlay();
      virtual IMap const &getCurrentMap() const;
      virtual IGUI &getGUI();
    private:
      Map m_map;
      GUI m_gui;
      std::vector<std::pair<std::string, SoundType> > m_soundsName;
      std::vector<NetworkPacket> m_net;
      std::vector<std::unique_ptr<ISprite> > m_sprites;
      std::vector<Sound> m_soundsPlay;
  };
}

extern "C"
{
  arcade::IGame *getGame();
}

#endif
