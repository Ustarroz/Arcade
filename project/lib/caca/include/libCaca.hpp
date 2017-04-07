#ifndef LIBCACA_HPP_
# define LIBCACA_HPP_

# include <vector>
# include <string>
# include <map>
# include <caca.h>
# include "Event.hpp"
# include "IMap.hpp"
# include "IGUI.hpp"
# include "IGfxLib.hpp"
# include "Common.hpp"

namespace arcade
{
  class libCaca: public IGfxLib
  {
    public:
      virtual ~libCaca();
      libCaca();
      libCaca(int, int);
      virtual bool pollEvent(Event &e);
      virtual bool doesSupportSound() const;
      virtual void loadSounds(std::vector<std::pair<std::string, SoundType> > const &sounds);
      virtual void soundControl(const Sound &sound);
      virtual void loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites);
      virtual void updateMap(IMap const &map);
      virtual void updateGUI(IGUI &gui);
      virtual void display();
      virtual void clear();
    private:
      void drawSquare(pos_t, int);
      int initCaca();
    private:
      int m_windowHeight;
      int m_windowWeight;
      bool m_doesSupportSound;
      caca_display_t *m_disp;
      caca_canvas_t *m_canvas;
      static std::map<int, KeyboardKey> m_keys;
  };
}

extern "C"
{
  arcade::IGfxLib *entryPoint();
}

#endif
