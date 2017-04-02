#include "Map.hpp"

namespace arcade
{

  Map::Map(size_t width, size_t height)
    : m_width(width), m_height(height)
  {
  }

  Map::~Map()
  {
  }

  size_t Map::getLayerNb() const
  {
    return (m_layers.size());
  }

  size_t Map::getWidth() const
  {
    return (m_width);
  }

  size_t Map::getHeight() const
  {
    return (m_height);
  }

  ITile const &Map::at(size_t layer, size_t x, size_t y) const
  {
    return (m_layers[layer].getTile(x, y));
  }

  void Map::setTile(int layer, int x, int y, Tile const &tile)
  {
    m_layers[layer].setTile(x, y, tile);
  }

  void Map::addLayer()
  {
    m_layers.push_back(Layer(m_width, m_height));
  }

  Layer &Map::getLayer(int i)
  {
    return (m_layers[i]);
  }
}
