#include "libSnake.hpp"
#include "Map.hpp"
#include "GameState.hpp"
#include "Tile.hpp"

namespace arcade
{
  Snake::Snake()
    : m_map(60, 60)
  {
    m_map.addLayer();
    m_map.setTile(0, 50, 50, Tile(TileType::BLOCK, TileTypeEvolution::BLOCK, {0, 0, 0, 255}, 0, 0, 0, 0));
  }

  Snake::~Snake()
  {
  }

  GameState Snake::getGameState() const
  {
    return (GameState::INGAME);
  }

  void Snake::notifyEvent(std::vector<Event> &&event)
  {
  }

  void Snake::notifyNetwork(std::vector<NetworkPacket> &&events)
  {
  }

  std::vector<NetworkPacket> &&Snake::getNetworkToSend()
  {
    return (std::move(m_net));
  }

  void Snake::process()
  {
  }

  std::vector<std::unique_ptr<ISprite>> &&Snake::getSpritesToLoad() const
  {
    std::vector<std::unique_ptr<ISprite> > sprites;
    return (std::move(sprites));
  }

  std::vector<std::pair<std::string, SoundType> > Snake::getSoundsToLoad() const
  {
    return (std::move(m_soundsName));
  }

  std::vector<int> &&Snake::getSoundsToPlay()
  {
    return (std::move(m_soundsPlay));
  }

  IMap const &Snake::getCurrentMap() const
  {
    return (m_map);
  }

  IGUI &Snake::getGUI()
  {
    return (m_gui);
  }
}

extern "C"
{
  arcade::IGame *getGame()
  {
    return (new arcade::Snake());
  }
}
