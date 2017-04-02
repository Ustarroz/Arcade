#ifndef LAYER_HPP_
# define LAYER_HPP_

# include <vector>
# include "Tile.hpp"

namespace arcade
{
  class Layer
  {
    public:
      explicit Layer(int width, int height);
      ~Layer();
      void setTile(int x, int y, Tile const &tile);
      Tile const &getTile(int x, int y)const;
    private:
      std::vector<Tile> m_col;
      std::vector<std::vector<Tile> > m_layer;
  };
}

#endif
