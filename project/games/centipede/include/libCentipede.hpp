#ifndef LIBCENTIPEDE_HPP_
# define LIBCENTIPEDE_HPP_

#include "IGame.hpp"
#include "Map.hpp"
#include "GUI.hpp"
#include "Protocol.hpp"
#include "GameGUI.hpp"
#include "gameCommon.hpp"

#define SHROOM_SCORE 50
#define CENTIPEDE_SCORE 75
#define CENTIPEDE_KILL_SCORE 200
#define CENTIPEDE_EMPTY_COLOR {100, 0, 0, 0}
#define CENTIPEDE_PART_COLOR {255, 255, 0, 255}
#define CENTIPEDE_HIGH_FILE "games/centipede_high.txt"

namespace arcade
{
  class Centipede: public IGame
  {
   public:
    struct CentiPart
    {
      CentiPart(PosGame pos, DirGame dir = DIR_RIGHT){
	_old_dir = dir;
	_pos = pos;
      };
      DirGame _old_dir;
      PosGame _pos;
    };

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
    virtual std::vector<NetworkPacket> getNetworkToSend();
    virtual bool hasNetwork() const;
    virtual void process();
    virtual std::vector<std::unique_ptr<ISprite>> getSpritesToLoad() const;
    virtual std::vector<std::pair<std::string, SoundType> > getSoundsToLoad() const;
    virtual std::vector<Sound> getSoundsToPlay();
    virtual IMap const &getCurrentMap() const;
    virtual IGUI &getGUI();
    virtual Position getPlayer() const;
   private:
    Map m_map;
    std::vector<std::pair<std::string, SoundType> > m_soundsName;
    std::vector<NetworkPacket> m_net;
    std::vector<std::unique_ptr<ISprite> > m_sprites;
    std::vector<std::vector<CentiPart>> m_centipede;
    std::vector<Shroom> m_shroom;
    size_t m_score;
    PosGame m_player;
    PosGame m_shoot;
    GameState m_state;
    GameProcess m_process;
    GameGUI m_gui;
    void useEvent(Event event);
    void useEventKeyBoard(Event event);
    void useEventKeyJoystick(Event event);
    void useEventKeyButton(Event event);
    void randShroom();
    void addShroom(int x, int y);
    void resetGame(bool first);
    void endGame();
    TileType checkPos(int x, int y, size_t limit_y);
    void shotAt(int x, int y);
    void shotShroom(int x, int y);
    void shotCentipede(int x, int y);
    void processShoot();
    void processCentipede();
    int checkHead(std::vector<CentiPart> &body);
    void addCentipede();
    std::vector<Sound> m_soundsPlay;
  };
}


extern "C"
{
arcade::IGame *getGame();
void	Play();
}

#endif
