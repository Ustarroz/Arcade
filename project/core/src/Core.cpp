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
    m_libsGfxName.push_back(fileName);
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
    Event e;
    memset(&e, 0, sizeof(Event));
    while (m_libsGfx[0]->pollEvent(e))
    {
      std::cout << "GameLoop" << std::endl;
      IMap const &map = m_libsGame[0]->getCurrentMap();
      m_libsGfx[0]->updateMap(map);
      m_libsGfx[0]->display();
    }

    return (0);
  }

  int Core::loadLibraries()
  {
    getLibsGfx();
    getLibsGame();
    for (unsigned long i = 0; i < m_libsGfxName.size(); i++)
    {
      if (setInterfaceGfx(m_libsGfxName[i]))
        return (1);
      else
        std::cout << "lib(" << m_libsGfxName[i] << ") " << i + 1 << "/" << m_libsGfxName.size() << std::endl;
    }
    for (unsigned long i = 0; i < m_libsGameName.size(); i++)
    {
      if (setInterfaceGame(m_libsGameName[i]))
        return (1);
      else
        std::cout << "lib(" << m_libsGameName[i] << ") " << i + 1 << "/" << m_libsGameName.size() << std::endl;
    }
    std::cout << "[Core] [OK] libs loaded" << std::endl;
    return (0);
  }

  int Core::setInterfaceGfx(std::string const &fileName)
  {
    void *sdlHandler = dlopen(fileName.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (sdlHandler == NULL)
    {
      m_error = "[Core] Error: Cannot load: " + fileName + " (" + dlerror() + ")";
      return (1);
    }
    std::function<IGfxLib *()> sdl = cast<IGfxLib *()>(dlsym(sdlHandler, "getLib"));
    m_handler.push_back(sdlHandler);
    IGfxLib *tmp = sdl();
    m_libsGfx.push_back(tmp);
    return (0);
  }

  int Core::setInterfaceGame(std::string const &fileName)
  {
    void *sdlHandler = dlopen(fileName.c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (sdlHandler == NULL)
    {
      m_error = "[Core] Error: Cannot load: " + fileName + " (" + dlerror() + ")";
      return (1);
    }
    std::function<IGame *()> sdl = cast<IGame *()>(dlsym(sdlHandler, "getGame"));
    m_handler.push_back(sdlHandler);
    IGame *tmp = sdl();
    m_libsGame.push_back(tmp);
    return (0);
  }

  void Core::getLibsGfx()
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
          for (std::vector<std::string>::iterator it = m_libsGfxName.begin(); it != m_libsGfxName.end(); ++it)
          {
            if (*it == tmp)
              shouldAdd = false;
          }
          if (shouldAdd)
            m_libsGfxName.push_back(tmp);
        }
      }
      closedir (dir);
    }
  }

  void Core::getLibsGame()
  {
    DIR *dir;
    struct dirent *ent;
    bool shouldAdd = true;
    if ((dir = opendir ("./games")) != NULL)
    {
      while ((ent = readdir (dir)) != NULL)
      {
        std::string tmp = "./games/";
        tmp += ent->d_name;
        if (std::strstr(tmp.c_str(), ".so") != NULL)
        {
          shouldAdd = true;
          for (std::vector<std::string>::iterator it = m_libsGameName.begin(); it != m_libsGameName.end(); ++it)
          {
            if (*it == tmp)
              shouldAdd = false;
          }
          if (shouldAdd)
            m_libsGameName.push_back(tmp);
        }
      }
      closedir (dir);
    }
  }
}
