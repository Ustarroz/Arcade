#include <vector>
#include <iostream>
#include <string>
#include <dlfcn.h>
#include "Core.hpp"

namespace arcade
{
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
    std::vector<std::string> libsName(getLibs());
    for (int i = 0; i < libsName.size(); i++)
    {
      if (setInterface(libsName[i]) == -1)
      {
        std::cerr << "SHOULD EXIT NOW!" << std::endl;
      }
    }
  }

  int Core::setInterface(std::string const &fileName)
  {
    void *sdlHandler = dlopen(fileName.c_str(), RTLD_LAZY);
    std::function<IGfxLib *()> sdl = cast<IGfxLib *()>(dlsym(sdlHandler, "entryPoint"));
    m_handler.push_back(sdlHandler);
    m_libsGame.push_back(sdl());
  }

  std::vector<std::string> &Core::getLibs() const
  {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./lib")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
              printf ("%s\n", ent->d_name);
                }
          closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
          return EXIT_FAILURE;
    }
  }
}
