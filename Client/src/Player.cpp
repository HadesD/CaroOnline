#include "app/Player.hpp"

namespace app {
  Player::Player()
  {
  }

  Player::~Player()
  {
  }

  void Player::setGame(std::shared_ptr<Game> game)
  {
    p_game = game;
  }

}
