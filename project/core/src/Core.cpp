#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include "Core.hpp"

namespace arcade
{
  Core::Core(std::string const &fileName)
  {
    m_libsName.push_back(fileName);
    loadLibraries();
  }

  Core::~Core()
  {
    for (unsigned long i = 0; i < m_handler.size(); i++)
    {
      dlclose(m_handler[i]);
    }
  }

  int Core::gameLoop()
  {
    //test call
    m_libsGame[0]->display(); 
    m_libsGame[0]->clear(); 

    return (0);
  }

  void Core::loadLibraries()
  {
    getLibs();
    std::cout << "LOL: " << m_libsName.size() << std::endl;
    for (unsigned long i = 0; i < m_libsName.size(); i++)
    {
      std::cout << "MDR" << std::endl;
      if (setInterface(m_libsName[i]))
        std::cerr << "SHOULD EXIT NOW!" << std::endl;
      else
        std::cout << "lib(" << m_libsName[i] << ") " << i << "/" << m_libsName.size() << std::endl;
    }
  }

  int Core::setInterface(std::string const &fileName)
  {
    std::cout << "DEBUG: " << fileName << std::endl;
    void *sdlHandler = dlopen(fileName.c_str(), RTLD_NOW | RTLD_GLOBAL);
    std::cout << dlerror() << std::endl;
    if (sdlHandler == NULL)
    {
      std::cout << "ERROR DLOPEN" << std::endl;
      return (1);
    }
    std::function<IGfxLib *()> sdl = cast<IGfxLib *()>(dlsym(sdlHandler, "entryPoint"));
    m_handler.push_back(sdlHandler);
    IGfxLib *tmp = sdl();
    m_libsGame.push_back(tmp);
    std::cout << "END" << std::endl;
    return (0);
  }

  void Core::getLibs()
  {
    DIR *dir;
    struct dirent *ent;
    bool shouldAdd = true;
    if ((dir = opendir ("./lib")) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        std::string tmp = "./lib/";
        tmp += ent->d_name;
        if (std::strstr(tmp.c_str(), ".so") != NULL)
        {
          std::cout << tmp << std::endl;
          shouldAdd = true;
          for (std::vector<std::string>::iterator it = m_libsName.begin(); it != m_libsName.end(); ++it)
          {
            if (*it == tmp)
              shouldAdd = false;
          }
          if (shouldAdd)
            m_libsName.push_back(tmp);
        }
      }
      closedir (dir);
    }
  }
}
