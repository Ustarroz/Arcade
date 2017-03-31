#ifndef CORE_HPP_
# define CORE_HPP_

# include <string>
# include <vector>
# include <functional>
# include "IGfxLib.hpp"

namespace arcade
{
  template <typename T>
    std::function<T> cast(void* f)
    {
          return static_cast<T*>(f);
    }

  class Core
  {
    public:
      ~Core();
      explicit Core(std::string const &fileName);
      int gameLoop();

    private:
      void loadLibraries();
      std::vector<std::string> &getLibs() const;
      int setInterface(std::string const &);

    private:
      std::vector<std::string> m_libsName;
      std::string fileName;
      std::vector<IGfxLib *> m_libsGame;
      std::vector<void *> m_handler;
  };
}

#endif /* !CORE_HPP_ */
