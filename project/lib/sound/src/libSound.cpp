#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "libSound.hpp"
#include "ISound.hpp"

namespace arcade
{
  libSound::libSound()
  {
    SDL_Init(SDL_INIT_VIDEO);
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
      std::cout << Mix_GetError() << std::endl;
    }
    Mix_AllocateChannels(10);
  }

  libSound::~libSound()
  {
    for (int i = 0; i < m_music.size(); i++)
    {
      Mix_FreeMusic(m_music[i]);
    }
    for (int i = 0; i < m_effect.size(); i++)
    {
      Mix_FreeChunk(m_effect[i]);
    }
    Mix_CloseAudio(); 
    SDL_Quit();
  }

  void libSound::loadMusic(std::string const &name)
  {
    /*Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
    Mix_PlayMusic(musique, -1);*/
    Mix_Music *music;
    music = Mix_LoadMUS(name.c_str());
    m_music.push_back(music);
  }

  void libSound::loadEffect(std::string const &name)
  {
    Mix_Chunk *effect;
    effect = Mix_LoadWAV(name.c_str());
    m_effect.push_back(effect);
  }

  void libSound::playMusic(int ndx, int nb)
  {
    Mix_PlayMusic(m_music[ndx], nb);
  }

  void libSound::playEffect(int ndx)
  {
    Mix_PlayChannel(-1, m_effect[ndx], 0);
  }
}

extern "C"
{
  arcade::ISound *getSound()
  {
    return (new arcade::libSound());
  }
}
