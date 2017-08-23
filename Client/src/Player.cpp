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

  void Player::onKeyboardEvent()
  {
    Game::GameBoard gb = p_game->getGameBoard();
    Game::Cursor gc = p_game->getCursor();

    int toX = gc.x;
    int toY = gc.y;

    switch (p_game->getKeyPushed())
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
      p_game->setCursor(Game::Cursor(toX, toY));
    }
    p_game->setGameBoard(gb);
  }
}
