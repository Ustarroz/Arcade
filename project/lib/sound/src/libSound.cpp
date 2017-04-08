#include <iostream>
#include <SFML/Audio.hpp>
#include "libSound.hpp"
#include "ISound.hpp"

namespace arcade
{
  libSound::libSound()
  {

    if (!m_music.openFromFile("assets/musics/stars.ogg"))
    {
      std::cout << "Error: Cannot open Music" << std::endl;
    }
    else
    {
      //m_music.play();
    }
  }

  libSound::~libSound()
  {
  }

  void libSound::loadMusic(std::string const &name)
  {
    (void)name;
  }

  void libSound::loadEffect(std::string const &name)
  {
    (void)name;
  }

  void libSound::playMusic(int ndx, int nb)
  {
    (void)ndx;
    (void)nb;
  }

  void libSound::playEffect(int ndx)
  {
    (void)ndx;
  }
}

extern "C"
{
  arcade::ISound *getSound()
  {
    return (new arcade::libSound());
  }
}
