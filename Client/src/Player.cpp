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

    switch (pGame->getKeyPushed())
    {
      case 10:
      case 32:
        {
          gb[cursor.x][cursor.y] = this->mark;
        }
        break;
      case 'k':
      case 'w':
        {
          if (cursor.x > 0)
          {
            cursor.x -= 1;
          }
        }
        break;
      case 'j':
      case 's':
        {
          if (cursor.x < (static_cast<int>(gb.size()) - 1))
          {
            cursor.x += 1;
          }
        }
        break;
      case 'h':
      case 'a':
        {
          if (cursor.y > 0)
          {
            cursor.y -= 1;
          }
        }
        break;
      case 'd':
      case 'l':
        {
          if (cursor.y < (static_cast<int>(gb.at(cursor.x).size()) - 1))
          {
            cursor.y += 1;
          }
        }
        break;
    }
    // if (!(cursor == Game::Cursor(toX, toY)))
    {
      pGame->setCursor(cursor);
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

  void Player::setMark(const int &mark)
  {
    this->mark = mark;
  }

  int Player::getMark() const
  {
    return this->mark;
  }
}
