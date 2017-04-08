#ifndef LIBSOUND_HPP_
# define LIBSOUND_HPP_

# include <iostream>
# include <vector>
# include <SDL/SDL_mixer.h>
# include "ISound.hpp"

namespace arcade
{
  class libSound: public ISound
  {
    public:
      libSound();
      virtual ~libSound();
      virtual void loadMusic(std::string const &);
      virtual void loadEffect(std::string const &);
      virtual void playMusic(int, int nb = -1);
      virtual void playEffect(int);
    private:
      std::vector<Mix_Music *> m_music;
      std::vector<Mix_Chunk *> m_effect;
  };
}

extern "C"
{
  arcade::ISound *getSound();
}
#endif
