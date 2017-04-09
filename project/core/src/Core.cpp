#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <zconf.h>
#include "Core.hpp"
#include "Component.hpp"
#include "GUI.hpp"
#include "ISound.hpp"

namespace arcade
{
  Core::Core(std::string const &fileName)
  {
    m_libsGfxName.push_back(fileName);
    m_handlerSound = dlopen("./music/lib_arcade_sound.so", RTLD_NOW | RTLD_GLOBAL);
    if (m_handlerSound != NULL)
    {
#ifdef DEBUG
      std::cout << "[Core] sound lib loaded" << std::endl;
#endif
      std::function<ISound *()> sound = cast<ISound *()>(dlsym(m_handlerSound, "getSound"));
      m_libSound = sound();
      /*m_libSound->loadMusic("./music/stars.mp3");
      m_libSound->playMusic(0);*/
     }
    else
    {
#ifdef DEBUG
      std::cout << "[Core] failed to open sound lib: " << dlerror() << std::endl;
#endif
    }
  }

  Core::~Core()
  {
    for (unsigned long i = 0; i < m_handlerGfx.size(); i++)
    {
      dlclose(m_handlerGfx[i]);
    }
    for (unsigned long i = 0; i < m_handlerGame.size(); i++)
    {
      dlclose(m_handlerGame[i]);
    }
  }

  std::string const &Core::getError() const
  {
    return (m_error);
  }

  int Core::gameLoop()
  {
#ifdef DEBUG
    std::cout << "GameLoop" << std::endl;
#endif
    Event e;
    memset(&e, 0, sizeof(Event));
    std::vector<Event> event_list;
    std::function<IGfxLib *()> gfxLaunch = cast<IGfxLib *()>(dlsym(m_handlerGfx[0], "getLib"));
    m_libsGfx = gfxLaunch();
    std::function<IGame *()> gameLaunch = cast<IGame *()>(dlsym(m_handlerGame[0], "getGame"));
    m_libsGame = gameLaunch();
    m_libsGfx->loadSprites(m_libsGame->getSpritesToLoad());
    bool go = true;
    int ndxGfx = 0;
    int ndxGame = 0;
    while (go)
    {
      while (m_libsGfx->pollEvent(e))
      {
        if (static_cast<KeyboardKey>(e.m_key) == KB_2 || static_cast<KeyboardKey>(e.m_key) == KB_3)
        {
#ifdef DEBUG
          std::cout << "switch gfx lib" << std::endl;
#endif
          delete m_libsGfx;
          if (static_cast<KeyboardKey>(e.m_key) == KB_2)
            --ndxGfx;
          else
            ++ndxGame;
          std::function<IGfxLib *()> gfxLaunch = cast<IGfxLib *()>(dlsym(m_handlerGfx[ndxGfx % m_handlerGfx.size()], "getLib"));
          m_libsGfx = gfxLaunch();
          e.kb_key = KB_0;
          m_libsGfx->loadSprites(m_libsGame->getSpritesToLoad());
        }
        else if (static_cast<KeyboardKey>(e.m_key) == KB_4 || static_cast<KeyboardKey>(e.m_key) == KB_5)
        {
#ifdef DEBUG
          std::cout << "switch game lib" << std::endl;
#endif
          delete m_libsGame;
          if (static_cast<KeyboardKey>(e.m_key) == KB_4)
            --ndxGame;
          else
            ++ndxGame;
          std::function<IGame *()> gameLaunch = cast<IGame *()>(dlsym(m_handlerGame[ndxGame % m_handlerGame.size()], "getGame"));
          m_libsGame = gameLaunch();
          e.kb_key = KB_0;
          m_libsGfx->loadSprites(m_libsGame->getSpritesToLoad());
        }
        else
          event_list.push_back(e);
      }
      if (m_libsGame->getGameState() == GameState::INGAME)
      {
        m_libsGfx->clear();
        event_list.clear();
        event_list.push_back(e);
        m_libsGame->notifyEvent(std::move(event_list));
        m_libsGame->process();
        IMap const &map = m_libsGame->getCurrentMap();
        IGUI &gui = m_libsGame->getGUI();
        m_libsGfx->updateMap(map);
        m_libsGfx->updateGUI(gui);
        m_libsGfx->display();
        usleep(100000);
        e.type = ET_NONE;
      }
      else if (m_libsGame->getGameState() == GameState::QUIT)
        go = false;
    }
    /*while (m_libsGfx->pollEvent(e))
    {
      if (static_cast<KeyboardKey>(e.m_key) == KB_1)
      {
#ifdef DEBUG
        std::cout << "switch gfx lib" << std::endl;
#endif
        delete m_libsGfx;
        ++m_ndx;
        std::function<IGfxLib *()> gfxLaunch = cast<IGfxLib *()>(dlsym(m_handlerGfx[m_ndx % m_handlerGfx.size()], "getLib"));
        m_libsGfx = gfxLaunch();
        e.kb_key = KB_0;
        m_libsGfx->loadSprites(m_libsGame->getSpritesToLoad());
      }
      m_libsGfx->clear();
      event_list.clear();
      event_list.push_back(e);
      m_libsGame->notifyEvent(std::move(event_list));
      m_libsGame->process();
      IMap const &map = m_libsGame->getCurrentMap();
      IGUI &gui = m_libsGame->getGUI();
      m_libsGfx->updateMap(map);
      m_libsGfx->updateGUI(gui);
      m_libsGfx->display();
      usleep(100000);
      e.type = ET_NONE;
    }*/

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
#ifdef DEBUG
      else
        std::cout << "lib(" << m_libsGfxName[i] << ") " << i + 1 << "/" << m_libsGfxName.size() << std::endl;
#endif
    }
    for (unsigned long i = 0; i < m_libsGameName.size(); i++)
    {
      if (setInterfaceGame(m_libsGameName[i]))
        return (1);
#ifdef DEBUG
      else
        std::cout << "lib(" << m_libsGameName[i] << ") " << i + 1 << "/" << m_libsGameName.size() << std::endl;
#endif
    }
#ifdef DEBUG
    std::cout << "[Core] [OK] libs loaded" << std::endl;
#endif
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
    m_handlerGfx.push_back(sdlHandler);
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
    m_handlerGame.push_back(sdlHandler);
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
