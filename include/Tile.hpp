#ifndef TILE_HPP_
# define TILE_HPP_

# include "ITile.hpp"
# include "Color.hpp"

namespace arcade
{
  class Tile: public ITile
  {
    public:
      explicit Tile(TileType, TileTypeEvolution, Color, size_t, size_t, double, double);
      virtual ~Tile();
      virtual TileType getType() const;
      virtual TileTypeEvolution getTypeEv() const;
      virtual Color getColor() const;
      virtual bool hasSprite() const;
      virtual size_t getSpriteId() const;
      virtual size_t getSpritePos() const;
      virtual double getShiftX() const;
      virtual double getShiftY() const;
    private:
      TileType m_type;
      TileTypeEvolution m_evo;
      Color m_color;
      size_t m_spriteId;
      size_t m_spritePos;
      double m_shiftX;
      double m_shiftY;
  };
}
#endif
