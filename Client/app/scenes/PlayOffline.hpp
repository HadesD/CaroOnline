#ifndef APP_SCENES_PLAY_OFFLINE_SCENE_HPP
#define APP_SCENES_PLAY_OFFLINE_SCENE_HPP
#include <vector>

#include "PlayScene.hpp"
#include "app/Point2D.hpp"
#include "../Common/GameBoard.hpp"

namespace app
{
  namespace core
  {
    class Game;
  }
  namespace objects {
    class Player;
  }
}

namespace app { namespace scenes {

  class PlayOfflineScene : public app::scenes::PlayScene
  {
    public:
      PlayOfflineScene(const std::shared_ptr<app::core::Game> &game);
      ~PlayOfflineScene();

    public:
      virtual void init();
      virtual void update(const float dt);
      virtual void draw();

    public:
      virtual void drawGameBoard();
      GameState checkMoveState(const app::Point2D &p);
      void checkFinish();
      void quit();

    // public:
    //   void addPlayer(const std::shared_ptr<app::objects::Player> &player);
    //   void removePlayer(const std::shared_ptr<app::objects::Player> &player);

    public:
      common::GameBoard getGameBoard() const;
      void setGameBoard(const common::GameBoard &/* gb */);

  };

} }

#endif
