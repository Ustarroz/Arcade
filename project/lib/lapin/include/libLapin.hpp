#ifndef LIBLAPIN_HPP_
# define LIBLAPIN_HPP_

# include <vector>
# include <string>
# include "Event.hpp"
# include "IMap.hpp"
# include "IGUI.hpp"
# include "IGfxLib.hpp"

namespace arcade
{
  class libLapin: public IGfxLib
  {
    public:
      virtual ~libLapin();
      libLapin();
      libLapin(int, int);
      virtual bool pollEvent(Event &e);
      virtual bool doesSupportSound() const;
      virtual void loadSounds(std::vector<std::string> const &sounds);
      virtual void soundControl(const Sound &sound);
      virtual void loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);
      virtual void updateMap(IMap const &map);
      virtual void updateGUI(IGUI &gui);
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
