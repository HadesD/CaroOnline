#include "app/scenes/PlayOfflineScene.hpp"

#include "app/objects/Player.hpp"

namespace app { namespace scenes {

  PlayOfflineScene::PlayOfflineScene(
    const std::shared_ptr<app::core::Game> &game
    ) : PlayScene(game)
  {
  }

  PlayOfflineScene::~PlayOfflineScene()
  {
  }

  void PlayOfflineScene::init()
  {
    auto me = std::make_shared<app::objects::Player>(
      app::objects::Player::Type::SELF
      );
    me->setIsTurn(true);
    this->addPlayer(me);
    this->setNextPlayer(me);

    auto g1 = std::make_shared<app::objects::Player>(
      app::objects::Player::Type::COMPUTER
      );
    this->addPlayer(g1);
  }

  void PlayOfflineScene::onSetGameBoardMove(const common::Point2D &p)
  {
  }

  bool PlayOfflineScene::quit()
  {
    if (PlayScene::quit())
    {
      return true;
    }

    return false;
  }

} }
