#include "Tile.hpp"

namespace arcade
{

  Tile::Tile(TileType type, TileTypeEvolution evo, Color color,
      size_t id, size_t pos, double x, double y, bool hasSprite)
    : m_type(type), m_evo(evo), m_color(color), m_spriteId(id),
    m_spritePos(pos), m_shiftX(x), m_shiftY(y), m_hasSprite(hasSprite)
  {
  }

  Tile::~Tile()
  {
  }

  TileType Tile::getType() const
  {
    return (m_type);
  }

  TileTypeEvolution Tile::getTypeEv() const
  {
    return (m_evo);
  }

  Color Tile::getColor() const
  {
    return (m_color);
  }

  bool Tile::hasSprite() const
  {
    return (m_hasSprite);
  }

  size_t Tile::getSpriteId() const
  {
    return (m_spriteId);
  }

  size_t Tile::getSpritePos() const
  {
    return (m_spritePos);
  }

  double Tile::getShiftX() const
  {
    return (m_shiftX);
  }

  double Tile::getShiftY() const
  {
    return (m_shiftY);
  }
}
