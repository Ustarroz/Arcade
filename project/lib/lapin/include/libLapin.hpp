#ifndef LIBLAPIN_HPP_
# define LIBLAPIN_HPP_

# define SIZE_TILE (30)

# include <vector>
# include <string>
# include "Event.hpp"
# include "IMap.hpp"
# include "IGUI.hpp"
# include "IGfxLib.hpp"
# include "lapin.h"
# include "Color.hpp"
# include "ITile.hpp"
# include "Common.hpp"
# include "Sound.hpp"

namespace arcade
{
  class libLapin: public IGfxLib
  {
    private:
      struct        t_program
      {
        char            *name;
        t_bunny_window    *win;
      };
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
    private:
      int initLapin();
      //t_bunny_response _bunnyMainLoop(void *);
      static t_bunny_response _bunnyUpdateMap(void *);
      static t_bunny_response _bunnyUpdateGUI(void *);
      static t_bunny_response _bunnyDisplay(void *);
      static t_bunny_response _bunnyClear(void *);
      void drawSquare(libLapin *, pos_t, int, Color);
    private:
      bool m_doesSupportSound;
      int m_windowHeight;
      int m_windowWeight;
      IMap const *m_map;
      IGUI *m_gui;
      t_program m_prog;
      t_bunny_pixelarray *m_render;
  };
}

extern "C"
{
  arcade::IGfxLib *getLib();
}

#endif
