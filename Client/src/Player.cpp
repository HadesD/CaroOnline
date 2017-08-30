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
    if (this->isTurn == false)
    {
      return;
    }

    Game::GameBoard gb = pGame->getGameBoard();

    switch (pGame->getKeyPushed())
    {
      case 10:
      case 32:
      case 'o':
      case 'e':
      case 'm':
        {
          if (gb.at(m_cursor.x).at(m_cursor.y) == 0)
          {
            this->isTurn = false;
            gb[m_cursor.x][m_cursor.y] = this->mark;
          }
        }
        break;
      case 65:
      case 'k':
      case 'w':
        {
          if (m_cursor.x > 0)
          {
            m_cursor.x--;
          }
        }
        break;
      case 66:
      case 'j':
      case 's':
        {
          if (m_cursor.x < (static_cast<int>(gb.size()) - 1))
          {
            m_cursor.x++;
          }
        }
        break;
      case 68:
      case 'h':
      case 'a':
        {
          if (m_cursor.y > 0)
          {
            m_cursor.y--;
          }
        }
        break;
      case 67:
      case 'd':
      case 'l':
        {
          if (m_cursor.y < (static_cast<int>(gb.at(m_cursor.x).size()) - 1))
          {
            m_cursor.y++;
          }
        }
        break;
    }

    pGame->setGameBoard(gb);

    if (this->isTurn == false)
    {
      pGame->checkFinish();

      pGame->setNextPlayer(pGame->getCurrentPlayer() + 1);
    }

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

  Point2D Player::getCursor() const
  {
    return this->m_cursor;
  }

  void Player::setCursor(const Point2D &c)
  {
    this->m_cursor = c;
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
