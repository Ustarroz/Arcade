#include "Sprite.hpp"

namespace arcade
{
  Sprite::Sprite(std::string name) : m_name(name)
  {
  }

  Sprite::~Sprite()
  {
  }

  size_t Sprite::spritesCount() const
  {
    return (1);
  }

  std::string Sprite::getGraphicPath(size_t pos) const
  {
    (void)pos;
    return (m_name);
  }

  char Sprite::getAscii(size_t pos) const
  {
    return ('A');
  }
}
