#ifndef LIBMENU_HPP_
# define LIBMENU_HPP_

# include "IGame.hpp"
# include "Map.hpp"
# include "GUI.hpp"
# include "ISprite.hpp"
# include "NetworkPacket.hpp"

namespace arcade
{
  class Menu: public IGame
  {
   public:
      Menu();
      virtual ~Menu();
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
      std::vector<NetworkPacket> m_net;
      std::vector<std::unique_ptr<ISprite>> m_sprite;
      std::vector<std::pair<std::string, SoundType> > m_soundsName;
      std::vector<Sound> m_soundsPlay;
  };
}

void	Play();

extern "C"
{
  arcade::IGame *getGame();
}

#endif
