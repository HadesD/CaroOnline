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
      case 'o':
      case 'e':
      case 'm':
        {
          if (gb.at(cursor.x).at(cursor.y) == 0)
          {
            gb[cursor.x][cursor.y] = this->mark;
            this->isTurn = false;
            Game::ListPlayer lp = pGame->getListPlayer();
            if (lp.back() == this->shared_from_this())
            {
              lp.front()->setIsTurn(true);
            }
            else
            {
              for (std::size_t i = 0; i < lp.size(); i++)
              {
                if (lp.at(i) == this->shared_from_this())
                {
                  lp.at(i + 1)->setIsTurn(true);
                  break;
                }
              }
            }
            // pGame->removePlayer(this->shared_from_this());
          }
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

  Game::Cursor Player::getCursor() const
  {
    return this->cursor;
  }

  int Player::getMark() const
  {
    return this->mark;
  }

  void Player::setIsTurn(const bool &isTurn)
  {
    this->isTurn = isTurn;
  }

  bool Player::getIsTurn() const
  {
    return this->isTurn;
  }
}
