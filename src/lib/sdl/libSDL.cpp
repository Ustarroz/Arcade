#include <vector>
#include <string>
#include <iostream>
#include "interface/Event.hpp"
#include "interface/IMap.hpp"
#include "interface/IGUI.hpp"
#include "interface/IGfxLib.hpp"
#include "lib/libSDL.hpp"

namespace arcade
{
  libSDL::libSDL()
    : m_doesSupportSound(true), m_windowHeight(640), m_windowWeight(640)
  {

  }

  libSDL::libSDL(int height, int weight)
    : m_doesSupportSound(true), m_windowHeight(height), m_windowWeight(weight)
  {

  }

  libSDL::~libSDL()
  {
  }

  bool libSDL::pollEvent(Event &e)
  {
    return (false);
  }

  bool libSDL::doesSupportSound() const
  {
    return (m_doesSupportSound);
  }

  void libSDL::loadSounds(std::vector<std::string> const &sound)
  {
  }

  void libSDL::playSound(int soundId)
  {
    std::cout << "PLAYSOUND func" << std::endl;
  }

  void libSDL::updateMap(IMap const &map)
  {
  }

  void libSDL::updateGUI(IGUI const &gui)
  {
  }

  void libSDL::display()
  {
    std::cout << "DISPLAY func" << std::endl;
  }

  void libSDL::clear()
  {
    std::cout << "CLEAR func" << std::endl;
  }
}

arcade::IGfxLib *entryPoint()
  {
    return (new arcade::libSDL());
  }
