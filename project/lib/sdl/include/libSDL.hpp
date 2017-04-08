#ifndef LIBSDL_HPP_
# define LIBSDL_HPP_

# include <vector>
# include <string>
# include <map>
# include <SDL2/SDL.h>
# include "Event.hpp"
# include "IMap.hpp"
# include "IGUI.hpp"
# include "IGfxLib.hpp"
# include "Sound.hpp"
# include "Common.hpp"

namespace arcade
{
  class libSDL: public IGfxLib
  {
    private:
      struct disp_t
      {
        SDL_Window *window;
        SDL_Surface *screen;
        SDL_Palette *palette;
      };
    public:
      virtual ~libSDL();
      libSDL();
      libSDL(int, int);
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
      int initSDL();
      void setPalette(SDL_Palette *);
      void drawSquare(SDL_Surface *, pos_t, int, SDL_Color *);
      void drawRect(SDL_Surface *, pos_t, int, int, SDL_Color *);
      void drawPixel(SDL_Surface *, pos_t, SDL_Color *);

    private:
      static std::map<SDL_Keycode, KeyboardKey> m_keys;
      bool m_doesSupportSound;
      int m_windowHeight;
      int m_windowWeight;
      disp_t m_disp;
  };
}

extern "C"
{
  arcade::IGfxLib *getLib();
}

#endif

