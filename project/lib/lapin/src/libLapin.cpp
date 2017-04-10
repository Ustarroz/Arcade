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
    bunny_stop(m_prog.win);
  }

  int libLapin::initLapin()
  {
    m_program.win = bunny_start(m_windowWeight, m_windowHeight, false, "Arcade - Lapin");
    if (program.win == NULL)
    {
      bunny_printlerr("Cannot open the window.");
      return (1);
    }
    program.name = "Arcade";
    bunny_clear(&program.win->buffer, PINK2);
    //bunny_printl("Press escape to exit. Click left to change the window color.");
    bunny_set_key_response(key_response);
    //bunny_set_click_response(click_response);
    bunny_set_loop_main_function(libLapin::_bunnyMainLoop);
    bunny_loop(program.win, 25, &program);
  }

  bool pollEvent(Event &e)
  {
  }

  bool doesSupportSound() const
  {
    return (false);
  }

  void loadSounds(std::vector<std::pair<std::string, SoundType > > const &sounds)
  {
    (void)sounds;
  }

  void soundControl(const Sound &sound)
  {
    (void)sound;
  }

  void loadSprites(std::vector<std::unique_ptr<ISprite>> &&sprites)
  {
    (void)sprites;
  }

  void updateMap(IMap const &map)
  {
  }

  void updateGUI(IGUI &gui)
  {
  }

  void display()
  {
  }

  void clear()
  {
  }

  static t_bunny_response libLapin::_bunnyMainLoop(void *data)
  {
    return (EXIT_ON_SUCCESS);
  }

}

extern "C"
{
  arcade::IGfxLib *entryPoint()
  {
    return (new arcade::libLapin());
  }
}
