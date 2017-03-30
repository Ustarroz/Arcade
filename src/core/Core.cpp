#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <dlfcn.h>
#include "core/Core.hpp"

namespace arcade
{
  Core::Core(std::string const &filename)
  {
    m_libsName.push_back(filename);
    loadLibraries();
  }

  Core::~Core()
  {
  }

  int Core::gameLoop()
  {
    //test call
   m_libsGame[0].playSound(); 
   m_libsGame[0].display(); 
   m_libsGame[0].clear(); 
  }

  void Core::loadLibraries()
  {
    //get others libName;
    std::cout << "Loading others" << std::endl;

    void *sdlHandler = dlopen(m_libsName[0].c_str(), RTLD_LAZY);
    std::function<IGfxLib *> sdl(dlsym(sdlHandler, "entryPoint"));
    m_libsGame.push_back(sdl());
  }
}
