#ifndef CORE_HPP_
# define CORE_HPP_

# include <string>
# include <vector>
# include <functional>
# include "IGfxLib.hpp"
# include "IGame.hpp"
# include "ISound.hpp"
# include "Menu.hpp"

namespace arcade
{
  template <typename T>
    std::function<T> cast(void* f)
    {
          return reinterpret_cast<T*>(f);
    }

  class Core
  {
    public:
      ~Core();
      explicit Core(std::string const &fileName);
      int loadLibraries();
      int gameLoop();
      std::string const &getError() const;

    private:
      void getLibsGfx();
      void getLibsGame();
      int setInterfaceGfx(std::string const &);
      int setInterfaceGame(std::string const &);
      GameState gameProcess(std::vector<Event> &&events);
      GameState menuProcess(std::vector<Event> &&events);

    private:
      std::vector<std::string> m_libsGfxName;
      IGfxLib * m_libsGfx;
      std::vector<std::string> m_libsGameName;
      IGame * m_libsGame;
      std::vector<void *> m_handlerGfx;
      std::vector<void *> m_handlerGame;
      void * m_handlerSound;
      std::string m_error;
      ISound *m_libSound;
      Menu m_menu;
      size_t m_game;
      size_t m_lib;
  };
}

#endif /* !CORE_HPP_ */
