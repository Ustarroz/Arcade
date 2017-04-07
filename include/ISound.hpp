#ifndef ISOUND_HPP_
# define ISOUND_HPP_

# include <iostream>

namespace arcade
{
  class ISound
  {
    public:
      virtual ~ISound() {};
      virtual void loadMusic(std::string const &) = 0;
      virtual void loadEffect(std::string const &) = 0;
      virtual void playMusic(int, int nb = -1) = 0;
      virtual void playEffect(int) = 0;
  };
}

#endif
