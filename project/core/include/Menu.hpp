#ifndef LIBMENU_HPP_
# define LIBMENU_HPP_

# include "Map.hpp"
# include "GUI.hpp"
# include "ISprite.hpp"
# include "NetworkPacket.hpp"
# include "Event.hpp"
# include "Sound.hpp"

#define MENU_LINE_0 0.2
#define MENU_LINE_05 0.3

#define MENU_LINE_1 0.4
#define MENU_LINE_2 0.55
#define MENU_LINE_3 0.7

#define MENU_COL_1 0.1
#define MENU_COL_2 0.4
#define MENU_COL_3 0.7

#define MENU_WIDTH 0.11
#define MENU_HEIGHT 0.03

#define MENU_POS_GAME 3
#define MENU_POS_NAME 5

#define MENU_COLOR_BG {0,0,0,255}
#define MENU_COLOR_TXT {255,255,255,255}
#define MENU_COLOR_SELECT {0,200,0,255}
#define MENU_COLOR_CURSOR {0,0,200,255}
#define MENU_COLOR_BOTH {0,200,200,255}
#define MENU_COLOR_TITLE {100,0,0,255}
#define MENU_COLOR_MAIN_TITLE {200,0,0,255}

namespace arcade
{
  class Menu
  {
   public:
    Menu();
    ~Menu();
    GameState getGameState() const;
    void notifyEvent(std::vector<Event> &&events);
    std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
    std::vector<Sound> getSoundsToPlay();
    IGUI &getGUI();
    std::string const & getGame();
    std::string const & getLib();
    std::string const & getName();
    size_t setLib(std::string const & lib);
    void setGameState(GameState state);
   private:

    void useEventKeyButton(Event const &event);
    void useEventKeyJoystick(Event const &event);
    void useEventKeyBoard(Event const &event);
    void useEvent(Event const &event);
    GUI m_gui;
    GameState m_state;
    size_t m_cursor;
    size_t m_lib;
    size_t m_game;
    std::string m_name;
    std::vector<std::pair<std::string, SoundType>> m_soundsName;
    std::vector<Sound> m_soundsPlay;
  };
}

#endif
