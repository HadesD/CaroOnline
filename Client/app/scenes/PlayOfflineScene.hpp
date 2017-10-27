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
      virtual void init() override;
      virtual bool quit() override;

  };

} }

#endif
