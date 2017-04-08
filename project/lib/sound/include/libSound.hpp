#ifndef LIBSOUND_HPP_
# define LIBSOUND_HPP_

# include <iostream>
# include <vector>
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
    sf::Music m_music;
  };
}

extern "C"
{
  arcade::ISound *getSound();
}
#endif
