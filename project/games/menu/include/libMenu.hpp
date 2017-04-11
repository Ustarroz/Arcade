#ifndef LIBMENU_HPP_
# define LIBMENU_HPP_

# include "IGame.hpp"
# include "Map.hpp"
# include "GUI.hpp"
# include "ISprite.hpp"
# include "NetworkPacket.hpp"
# include "../../common/include/gameCommon.hpp"

#define MENU_LINE_0 0.2
#define MENU_LINE_05 0.3

#define MENU_LINE_1 0.4
#define MENU_LINE_2 0.55
#define MENU_LINE_3 0.7

#define MENU_COL_1 0.1
#define MENU_COL_2 0.4
#define MENU_COL_3 0.7

#define MENU_WIDTH 100
#define MENU_HEIGHT 17

#define MENU_POS_GAME 3
#define MENU_POS_NAME 5

#define MENU_COLOR_BG {0,0,0,255}
#define MENU_COLOR_TXT {255,255,255,255}
#define MENU_COLOR_SELECT {0,100,0,255}
#define MENU_COLOR_CURSOR {0,0,100,255}
#define MENU_COLOR_BOTH {0,100,100,255}
#define MENU_COLOR_TITLE {100,0,0,255}
#define MENU_COLOR_MAIN_TITLE {200,0,0,255}

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
      virtual std::vector<NetworkPacket> getNetworkToSend();
      virtual bool hasNetwork() const;
      virtual void process();
      virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;
      virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
      virtual std::vector<Sound> getSoundsToPlay();
      virtual IMap const &getCurrentMap() const;
      virtual IGUI &getGUI();
      std::string const & getGame();
      std::string const & getLib();
      std::string const & getName();
      private:

    void	useEventKeyButton(Event event);
    void 	useEventKeyJoystick(Event event);
    void	useEventKeyBoard(Event event);
    void 	useEvent(Event event);
    std::vector <Component> 	pos;
    Map 			m_map;
    GUI 			m_gui;
    GameState 			m_state;
    std::vector<NetworkPacket> 	m_net;
    size_t			m_cursor;
    size_t			m_lib;
    size_t			m_game;
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
