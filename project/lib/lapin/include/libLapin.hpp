#ifndef LIBLAPIN_HPP_
# define LIBLAPIN_HPP_

# include <vector>
# include <string>
# include "Event.hpp"
# include "IMap.hpp"
# include "IGUI.hpp"
# include "IGfxLib.hpp"
# include "lapin.h"

namespace arcade
{
  class libLapin: public IGfxLib
  {
    public:
      virtual ~libLapin();
      libLapin();
      libLapin(int, int);
      bool pollEvent(Event &e);
      bool doesSupportSound() const;
      void loadSounds(std::vector<std::pair<std::string, SoundType > > const &sounds);
      void soundControl(const Sound &sound);
      void loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);
      void updateMap(IMap const &map);
      void updateGUI(IGUI &gui);
      void display();
      void clear();
      static t_bunny_response _bunnyMainLoop(void *);
    private:
      int initLapin();
    private:
      bool m_doesSupportSound;
      int m_windowHeight;
      int m_windowWeight;
      t_program prog;
  };
}

extern "C"
{
  arcade::IGfxLib *entryPoint();
}

#endif
