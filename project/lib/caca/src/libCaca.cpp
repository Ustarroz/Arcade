#include <vector>
#include <string>
#include <iostream>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "libCaca.hpp"

namespace arcade
{
  libCaca::libCaca()
    : m_doesSupportSound(true), m_windowHeight(640), m_windowWeight(640)
  {

  }

  libCaca::libCaca(int height, int weight)
    : m_doesSupportSound(true), m_windowHeight(height), m_windowWeight(weight)
  {

  }

  libCaca::~libCaca()
  {
  }

  bool libCaca::pollEvent(Event &e)
  {
    return (false);
  }

  bool libCaca::doesSupportSound() const
  {
    return (m_doesSupportSound);
  }

  void libCaca::loadSounds(std::vector<std::string> const &sound)
  {
  }

  void libCaca::soundControl(const Sound &sound)
  {
    std::cout << "PLAYSOUND func" << std::endl;
  }

  void libCaca::loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
  }

  void libCaca::updateMap(IMap const &map)
  {
  }

  void libCaca::updateGUI(IGUI &gui)
  {
  }

  void libCaca::display()
  {
    std::cout << "DISPLAY func" << std::endl;
  }

  void libCaca::clear()
  {
    std::cout << "CLEAR func" << std::endl;
  }
}

extern "C"
{
  arcade::IGfxLib *entryPoint()
  {
    return (new arcade::libCaca());
  }
}
