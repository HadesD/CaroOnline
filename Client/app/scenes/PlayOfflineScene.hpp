#ifndef APP_SCENES_PLAY_OFFLINE_SCENE_HPP
#define APP_SCENES_PLAY_OFFLINE_SCENE_HPP
#include "PlayScene.hpp"

namespace app { namespace scenes {

  class PlayOfflineScene : public app::scenes::PlayScene
  {
    public:
      PlayOfflineScene(const std::shared_ptr<app::core::Game> &game);
      ~PlayOfflineScene();

    public:
      virtual void onSetGameBoardMove(const common::Point2D &p) override;
      virtual void quit() override;

    // public:
    //   void init();
    //   void update(const float dt);
    //   void draw();
    //
    // public:
    //   void drawGameBoard();
    //   GameState checkMoveState(const common::Point2D &p);
    //   void checkFinish();
    //   void quit();

    // public:
    //   void addPlayer(const std::shared_ptr<app::objects::Player> &player);
    //   void removePlayer(const std::shared_ptr<app::objects::Player> &player);

    // public:
    //   common::GameBoard getGameBoard() const;
    //   void setGameBoard(const common::GameBoard &#<{(| gb |)}>#);

  };

} }

#endif
