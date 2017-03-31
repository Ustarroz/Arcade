#include <vector>
#include <string>
#include <iostream>
#include "Event.hpp"
#include "IMap.hpp"
#include "IGUI.hpp"
#include "IGfxLib.hpp"
#include "libLapin.hpp"

namespace arcade
{
  libLapin::libLapin()
    : m_doesSupportSound(true), m_windowHeight(640), m_windowWeight(640)
  {

  }

  libLapin::libLapin(int height, int weight)
    : m_doesSupportSound(true), m_windowHeight(height), m_windowWeight(weight)
  {

  }

  libLapin::~libLapin()
  {
  }

  bool libLapin::pollEvent(Event &e)
  {
    return (false);
  }

  bool libLapin::doesSupportSound() const
  {
    return (m_doesSupportSound);
  }

  void libLapin::loadSounds(std::vector<std::string> const &sound)
  {
  }

  void libLapin::playSound(int soundId)
  {
    std::cout << "PLAYSOUND func" << std::endl;
  }

  void libLapin::updateMap(IMap const &map)
  {
  }

  void libLapin::updateGUI(IGUI const &gui)
  {
  }

  void libLapin::display()
  {
    std::cout << "DISPLAY func" << std::endl;
  }

  void libLapin::clear()
  {
    std::cout << "CLEAR func" << std::endl;
  }
}

arcade::IGfxLib *entryPoint()
  {
    return (new arcade::libLapin());
  }
