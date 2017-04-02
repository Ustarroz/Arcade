#ifndef CORE_HPP_
# define CORE_HPP_

# include <string>
# include <vector>
# include <functional>
# include "IGfxLib.hpp"
# include "IGame.hpp"

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

    private:
      std::vector<std::string> m_libsGfxName;
      std::vector<IGfxLib *> m_libsGfx;
      std::vector<std::string> m_libsGameName;
      std::vector<IGame *> m_libsGame;
      std::vector<void *> m_handler;
      std::string m_error;
  };
}

#endif /* !CORE_HPP_ */
