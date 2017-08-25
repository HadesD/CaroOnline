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

    
    switch (pGame->getKeyPushed())
    {
      case 10:
      case 32:
      case 'o':
      case 'e':
      case 'm':
        {
          Game::GameBoard gb = pGame->getGameBoard();

          if (gb.at(cursor.x).at(cursor.y) == 0)
          {
            this->isTurn = false;
            gb[cursor.x][cursor.y] = this->mark;
            pGame->setNextPlayer(pGame->getNextPlayer() + 1);
          }
          
          pGame->setGameBoard(gb);
        }
        break;
      case 'k':
      case 'w':
        {
          if (cursor.x > 0)
          {
            cursor.x--;
          }
        }
        break;
      case 'j':
      case 's':
        {
          if (cursor.x < (static_cast<int>(gb.size()) - 1))
          {
            cursor.x++;
          }
        }
        break;
      case 'h':
      case 'a':
        {
          if (cursor.y > 0)
          {
            cursor.y--;
          }
        }
        break;
      case 'd':
      case 'l':
        {
          if (cursor.y < (static_cast<int>(gb.at(cursor.x).size()) - 1))
          {
            cursor.y++;
          }
        }
        break;
    }

    if (this->isTurn == false)
    {
      pGame->checkFinish();
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
