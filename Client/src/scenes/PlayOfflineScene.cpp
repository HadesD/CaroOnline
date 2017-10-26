#include "app/scenes/PlayOfflineScene.hpp"

namespace app { namespace scenes {

  PlayOfflineScene::PlayOfflineScene(
    const std::shared_ptr<app::core::Game> &game
    ) : PlayScene(game)
  {
  }

  PlayOfflineScene::~PlayOfflineScene()
  {
  }

  void PlayOfflineScene::onSetGameBoardMove(const common::Point2D &p)
  {
  }

} }
