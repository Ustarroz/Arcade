#include "Layer.hpp"

namespace arcade
{
  Layer::Layer(int width, int height)
  {
    Color a(255, 0, 0, 255);
    m_col = std::vector<Tile>(width, Tile(TileType::BLOCK, TileTypeEvolution::BLOCK, a, 0, 0, 0, 0));
    m_layer = std::vector<std::vector<Tile> > (height, m_col);
  }

  Layer::~Layer()
  {
  }

  void Layer::setTile(int x, int y, Tile const &tile)
  {
    m_layer[y][x] = tile;
  }

  Tile const &Layer::getTile(int x, int y) const
  {
    return (m_layer[y][x]);
  }

}
