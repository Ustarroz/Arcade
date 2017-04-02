#ifndef MAP_HPP_
# define MAP_HPP_

# include <vector>
# include "IMap.hpp"
# include "Tile.hpp"
# include "Layer.hpp"

namespace arcade
{
  class Map: public IMap
  {
    public:
      explicit Map(size_t, size_t);
      virtual ~Map();
      virtual size_t getLayerNb() const;
      virtual size_t getWidth() const;
      virtual size_t getHeight() const;
      virtual ITile const &at(size_t layer, size_t x, size_t y) const;
      void addLayer();
      Layer &getLayer(int);
      void setTile(int layer, int x, int y, Tile const &tile);
    private:
      std::vector<Layer> m_layers;
      size_t m_width;
      size_t m_height;
  };
}

#endif
