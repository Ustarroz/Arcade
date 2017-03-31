#ifndef CORE_HPP_
# define CORE_HPP_

# include <string>
# include <vector>
# include "IGfxLib.hpp"

namespace arcade
{
  class Core
  {
    public:
      ~Core();
      explicit Core(std::string const &fileName);
      int gameLoop();
    private:
      void loadLibraries();
      std::vector<std::string> m_libsName;
      std::string fileName;
      std::vector<IGfxLib *> m_libsGame;
      void *sdlHandler;
  };
}

#endif /* !CORE_HPP_ */
