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
    pGame = game;
  }

  void Player::onKeyboardEvent()
  {
    Game::GameBoard gb = pGame->getGameBoard();
    Game::Cursor gc = pGame->getCursor();

    int toX = gc.x;
    int toY = gc.y;

    switch (pGame->getKeyPushed())
    {
      case 10:
      case 32:
        {
        }
        break;
      case 'k':
      case 'w':
        {
          if (gc.x > 0)
          {
            toX -= 1;
          }
        }
        break;
      case 'j':
      case 's':
        {
          if (gc.x < (static_cast<int>(gb.size()) - 1))
          {
            toX += 1;
          }
        }
        break;
      case 'h':
      case 'a':
        {
          if (gc.y > 0)
          {
            toY -= 1;
          }
        }
        break;
      case 'd':
      case 'l':
        {
          if (gc.y < (static_cast<int>(gb.at(gc.x).size()) - 1))
          {
            toY += 1;
          }
        }
        break;
    }
    if (!(gc == Game::Cursor(toX, toY)))
    {
      pGame->setCursor(Game::Cursor(toX, toY));
    }
    pGame->setGameBoard(gb);
  }

  void Player::setId(const int &id)
  {
    this->id = id;
  }

  int Player::getId() const
  {
    return this->id;
  }
}
