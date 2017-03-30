#ifndef LIBSDL_HPP_
# define LIBSDL_HPP_

# include <vector>
# include <string>
# include "interface/Event.hpp"
# include "interface/IMap.hpp"
# include "interface/IGUI.hpp"
# include "interface/IGfxLib.hpp"

namespace arcade
{
  class libSDL: public IGfxLib
  {
    public:
      virtual ~libSDL();
      libSDL();
      libSDL(int, int);
      virtual bool pollEvent(Event &e);
      virtual bool doesSupportSound() const;
      virtual void loadSounds(std::vector<std::string> const &sounds);
      virtual void playSound(int soundId);
      virtual void updateMap(IMap const &map);
      virtual void updateGUI(IGUI const &gui);
      virtual void display();
      virtual void clear();
    private:
      bool m_doesSupportSound;
      int m_windowHeight;
      int m_windowWeight;
      
  };
}
extern "C"
{
  arcade::IGfxLib *entryPoint();
}

#endif
