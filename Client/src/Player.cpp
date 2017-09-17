#include <ctime>

#include "app/Player.hpp"

#include "../Common/net/Connection.hpp"

namespace app {

  /*
   * Player::Player()
   * {
   *   m_isReady = false;
   * }
   */

  Player::Player(asio::io_service &s) :
    m_pIoService(s)
  {
    std::srand(0);
    m_pConnection = std::make_shared<common::net::Connection>(
      m_pIoService,
      0
      );
  }

  Player::~Player()
  {
    // delete m_pScene;
  }

  void Player::update()
  {
    std::cout << std::rand() << std::endl;
    this->waitKeyboardEvent();

    common::net::Connection::Endpoint dis(
      common::net::Connection::Protocol::v4(),
      8889
      );

    m_pConnection->getSocket().async_send_to(
    // m_pConnection->getSocket().send_to(
      asio::buffer("ffff", 6),
      dis,
      std::bind([&](const std::error_code &e){

      }, this, std::placeholders::_1)
      );
  }

  void Player::waitKeyboardEvent()
  {
    this->onKeyboardEvent();
  }

  void Player::onKeyboardEvent()
  {
    if (this->m_isTurn == false)
    {
      return;
    }

    if (m_pScene == nullptr)
    {
      throw std::runtime_error("Not found scene");
    }

    if (m_kbhit.kbhit())
    {
      int keyPushed = m_kbhit.getch();

      app::scenes::PlayScene::GameBoard gb = m_pScene->getGameBoard();

      switch (keyPushed)
      {
        case 'q':
          {
            m_pScene->quit();
          }
          break;
        case 10:
        case 32:
        case 'o':
        case 'e':
        case 'm':
          {
            if (gb.at(m_cursor.x).at(m_cursor.y) == 0)
            {
              this->m_isTurn = false;
              gb[m_cursor.x][m_cursor.y] = this->m_mark;
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

      m_pScene->setGameBoard(gb);

      if (this->m_isTurn == false)
      {
        m_pScene->checkFinish();

        m_pScene->setNextPlayer(m_pScene->getCurrentPlayer() + 1);
      }
    }
  }

  void Player::setId(const int &id)
  {
    this->m_id = id;
  }

  int Player::getId() const
  {
    return this->m_id;
  }

  void Player::setMark(const int &mark)
  {
    this->m_mark = mark;
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
    return this->m_mark;
  }

  void Player::setIsTurn(const bool &isTurn)
  {
    this->m_isTurn = isTurn;
  }

  bool Player::getIsTurn() const
  {
    return this->m_isTurn;
  }

  void Player::setScene(std::shared_ptr<scenes::PlayScene> scene)
  {
    m_pScene = scene;
  }

  void Player::setScene(scenes::PlayScene *scene)
  {
    this->setScene(std::shared_ptr<scenes::PlayScene>(scene));
  }

}

