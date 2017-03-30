#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <dlfcn.h>
#include "core/Core.hpp"

namespace arcade
{
  template <typename T>
    std::function<T> cast(void* f)
    {
          return static_cast<T*>(f);
    }
  Core::Core(std::string const &filename)
  {
    m_libsName.push_back(filename);
    loadLibraries();
  }

  Core::~Core()
  {
    dlclose(sdlHandler);
  }

  int Core::gameLoop()
  {
    //test call
   m_libsGame[0]->playSound(0); 
   m_libsGame[0]->display(); 
   m_libsGame[0]->clear(); 
   return (0);
  }

  void Core::loadLibraries()
  {
    //get others libName;
    std::cout << "Loading others" << std::endl;

    sdlHandler = dlopen(m_libsName[0].c_str(), RTLD_LAZY);
    std::function<IGfxLib *()> sdl = reinterpret_cast<IGfxLib *(*)()>(dlsym(sdlHandler, "entryPoint"));
    m_libsGame.push_back(sdl());
  }
}
