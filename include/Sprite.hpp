#ifndef SPRITE_HPP_
# define SPRITE_HPP_

# include "ISprite.hpp"

namespace arcade
{
  class Sprite: public ISprite
  {
    public:
      explicit Sprite(std::string);
      virtual ~Sprite();
      virtual size_t spritesCount() const;
      virtual std::string getGraphicPath(size_t pos) const;
      virtual char getAscii(size_t pos) const;
    private:
      std::string m_name;
  };
}

#endif
