#ifndef LIBCENTIPEDE_HPP_
# define LIBCENTIPEDE_HPP_

#include "IGame.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Protocol.hpp"
#include "GameGUI.hpp"
#include "gameCommon.hpp"

#define MAXSCORE 500
#define MINSCORE 50
#define STEPSCORE 10
#define SHROOM_SCORE 50
#define CENTIPEDE_HIGH_FILE "games/centipede_high.txt"

namespace arcade
{
  class Centipede: public IGame
  {
   public:
    struct Shroom{
      Position _pos;
      int _life;
      Tile _tile = Tile(TileType::EMPTY, TileTypeEvolution::EMPTY,
			{0, 0, 0, 0}, 0, 0, 0, 0);
    };
    Centipede();
    virtual ~Centipede();
    virtual GameState getGameState() const;
    virtual void notifyEvent(std::vector<Event> &&events);
    virtual void notifyNetwork(std::vector<NetworkPacket> &&events);
    virtual std::vector<NetworkPacket> &&getNetworkToSend();
    virtual void process();
    virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;
    virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
    virtual std::vector<Sound> getSoundsToPlay();
    virtual IMap const &getCurrentMap() const;
    virtual IGUI &getGUI();
    virtual std::vector<Position> getPlayer() const;
   private:
    Map m_map;
    std::vector<std::pair<std::string, SoundType> > m_soundsName;
    std::vector<NetworkPacket> m_net;
    std::vector<std::unique_ptr<ISprite> > m_sprites;
    std::vector<PosGame> m_centipede;
    size_t m_appleScore;
    std::vector<Shroom> m_shroom;
    size_t m_score;
    PosGame m_player;
    PosGame m_shoot;
    GameState m_state;
    GameGUI m_gui;
    void useEvent(Event event);
    void useEventKeyBoard(Event event);
    void useEventKeyJoystick(Event event);
    void useEventKeyButton(Event event);
    void randShroom();
    void addShroom(int x, int y);
    void addCentipede();
    void resetGame(bool first);
    void endGame();
    bool checkPos(int x, int y, size_t limit_y);
    void shotAt(int x, int y);
    void shotShroom(int x, int y);
    void processShoot();
    std::vector<Sound> m_soundsPlay;
  };
}


extern "C"
{
arcade::IGame *getGame();
void	Play();
}

#endif
