#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include "Core.hpp"
#include "Component.hpp"
#include "GUI.hpp"

namespace arcade
{
  Core::Core(std::string const &fileName)
  {
    m_libsName.push_back(fileName);
  }

  Core::~Core()
  {
    for (unsigned long i = 0; i < m_handler.size(); i++)
    {
      dlclose(m_handler[i]);
    }
  }

  std::string const &Core::getError() const
  {
    return (m_error);
  }

  int Core::gameLoop()
  {
    //test call
    std::cout << "GameLoop" << std::endl;
    GUI a;
    m_libsGame[0]->updateGUI(a);
    m_libsGame[0]->display();

    return (0);
  }

  int Core::loadLibraries()
  {
    getLibs();
    for (unsigned long i = 0; i < m_libsName.size(); i++)
    {
      if (setInterface(m_libsName[i]))
        return (1);
      else
        std::cout << "lib(" << m_libsName[i] << ") " << i + 1 << "/" << m_libsName.size() << std::endl;
    }
    std::cout << "[Core] [OK] libs loaded" << std::endl;
    return (0);
  }

  int Core::setInterface(std::string const &fileName)
  {
    void *sdlHandler = dlopen(fileName.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (sdlHandler == NULL)
    {
      m_error = "[Core] Error: Cannot load: " + fileName + " (" + dlerror() + ")";
      return (1);
    }
    std::function<IGfxLib *()> sdl = cast<IGfxLib *()>(dlsym(sdlHandler, "entryPoint"));
    m_handler.push_back(sdlHandler);
    IGfxLib *tmp = sdl();
    m_libsGame.push_back(tmp);
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
