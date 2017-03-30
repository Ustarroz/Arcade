#ifndef CORE_HPP_
# define CORE_HPP_
# undef EXIT_FAILURE
# define EXIT_FAILURE 84
# undef EXIT_SUCCESS
# define EXIT_SUCCESS 0

# include <string>
# include <vector>
# include <interface/IGfxLib.hpp>

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
      const std::vector<std::string const &> m_libsName;
      const std::vector<IGfxLib *> m_libsGame;
  };
}

#endif /* !CORE_HPP_ */
