#include <iostream>
#include <cassert>

#include "app/scenes/PlayScene.hpp"
#include "app/scenes/IntroScene.hpp"

#include "app/core/Game.hpp"
#include "app/Config.hpp"
#include "app/Player.hpp"
#include "../Common/Config.hpp"

namespace app { namespace scenes {

  PlayScene::PlayScene(const std::shared_ptr<app::core::Game> &game) : app::Scene(game)
  {
    m_gameBoard.assign(
      common::config::gameBoardRows,
      std::vector< int >(common::config::gameBoardCols, 0)
      );

    m_gameBoardOneObjSize = 3;
  }

  PlayScene::~PlayScene()
  {
  }

  void PlayScene::init()
  {
    std::shared_ptr<app::Player> me1(new app::Player());
    me1->setIsTurn(true);
    me1->setMark(m_listPlayer.size()+1);
    this->addPlayer(me1);

    std::shared_ptr<app::Player> me2(new app::Player());
    me2->setMark(m_listPlayer.size()+1);
    this->addPlayer(me2);
  }

  void PlayScene::draw()
  {
    this->drawGameBoard();
  }

  void PlayScene::quit()
  {
    m_pGame->quit();
  }

  void PlayScene::update(const float &/* dt */)
  {
    if (m_isFinish == true)
    {
      std::cout << "Winner: " << m_currentPlayer << std::endl;
      m_pGame->quit();
    }

    if (m_listPlayer.size() > 0)
    {
      this->m_cursor = m_listPlayer.at(m_currentPlayer)->getCursor();

      std::weak_ptr<Player> p = m_listPlayer.at(m_currentPlayer);
      if (auto pP = p.lock())
      {
        p.lock()->waitKeyboardEvent();
      }
    }
  }

  void PlayScene::drawGameBoard()
  {
    assert((m_gameBoardOneObjSize % 2) != 0);
    // Barrier
    std::cout << "Current Player: " << m_currentPlayer << std::endl;
    auto drawBarrier = [](const int &len){
      for (std::size_t i = 0; i < common::config::gameBoardCols; i++)
      {
        std::cout << '+';
        std::cout << std::string(len, '-');
      }
      std::cout << '+';
      std::cout << std::endl;
    };

    // Body
    auto drawLine = [=](const std::string &s){
      std::cout << '|';
      std::cout << std::string(m_gameBoardOneObjSize / 2, ' ');
      std::cout << s;
      std::cout << std::string(m_gameBoardOneObjSize / 2, ' ');
    };

    for (size_t x = 0; x < m_gameBoard.size(); x++)
    {
      drawBarrier(m_gameBoardOneObjSize);
      // for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      // {
      //   drawBody(" ");
      // }
      // std::cout << '|';
      // std::cout << std::endl;
      for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      {
        std::string curr;
        std::string color;

        switch (m_gameBoard.at(x).at(y))
        {
          default:
          case 0:
            {
              color.clear();
              curr = " ";
            }
            break;
          case 1:
            {
              color = "\e[38;5;196m";
              curr = "x";
            }
            break;
          case 2:
            {
              color = "\e[38;5;37m";
              curr = "o";
            }
            break;
          case 3:
            {
              color = "\e[38;5;50m";
              curr = "z";
            }
            break;

        }
        if (m_cursor == Point2D(x, y))
        {
          color = "\e[48;5;255m";
        }
        curr += "\e[0m";

        drawLine(color + curr);
      }
      std::cout << '|';
      std::cout << std::endl;
      // for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      // {
      //   drawBody(" ");
      // }
      // std::cout << '|';
      // std::cout << std::endl;
    }
    drawBarrier(m_gameBoardOneObjSize);
  }


  void PlayScene::checkFinish()
  {
    int xP, yP, x0, y0, xMaxSize, yMaxSize;

    std::weak_ptr<Player> p = m_listPlayer.at(m_currentPlayer);

    if (auto pP = p.lock())
    {
      xP = pP->getCursor().x;
      yP = pP->getCursor().y;
    }
    else
    {
      throw std::runtime_error("Cant lock player: " + std::to_string(m_currentPlayer));
    }

    x0 = std::max(xP - common::config::maxCoupleCount, 0);
    y0 = std::max(yP - common::config::maxCoupleCount, 0);

    xMaxSize = std::min(xP + common::config::maxCoupleCount + 1,
                        static_cast<int>(m_gameBoard.size()));
    yMaxSize = std::min(yP + common::config::maxCoupleCount + 1,
                        static_cast<int>(m_gameBoard.at(xMaxSize-1).size()));

    // Game board likes:
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    int count;

    // Check Hoz line
    count = 0;
    for (int y = y0; y < yMaxSize - 1; y++)
    {
      if (
        (m_gameBoard.at(xP).at(y) == p.lock()->getMark()) &&
        (m_gameBoard.at(xP).at(y + 1) == p.lock()->getMark())
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        this->m_isFinish = true;
        return;
      }
    }

    // Check vert
    count = 0;
    for (int x = x0; x < xMaxSize - 1; x++)
    {
      if (
        (m_gameBoard.at(x).at(yP) == p.lock()->getMark()) &&
        (m_gameBoard.at(x + 1).at(yP) == p.lock()->getMark())
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        this->m_isFinish = true;
        return;
      }
    }

    // Check diagonal L->R
    count = 0;
    for (int x = x0, y = y0; x < xMaxSize - 1; x++, y++)
    {
      if (y >= yMaxSize - 1)
      {
        break;
      }
      if (
        (m_gameBoard.at(x).at(y) == p.lock()->getMark()) &&
        (m_gameBoard.at(x + 1).at(y + 1) == p.lock()->getMark())
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        this->m_isFinish = true;
        return;
      }
    }

    // Check diagonal R->L
    count = 0;
    for (int x = x0, y = yMaxSize - 1; x < xMaxSize - 1; x++, y--)
    {
      if (y <= y0)
      {
        break;
      }
      if (
        (m_gameBoard.at(x).at(y) == p.lock()->getMark()) &&
        (m_gameBoard.at(x + 1).at(y - 1) == p.lock()->getMark())
        )
      {
        count++;
      }
      else
      {
        count = 0;
      }

      if (count >= common::config::maxCoupleCount)
      {
        this->m_isFinish = true;
        return;
      }
    }
  }

  PlayScene::GameState PlayScene::checkMoveState(const app::Point2D &p)
  {
    return PlayScene::GameState::WIN;
  }

  Point2D PlayScene::getCursor() const
  {
    return m_cursor;
  }

  void PlayScene::setCursor(const Point2D &c)
  {
    m_cursor = c;
  }

  PlayScene::GameBoard PlayScene::getGameBoard() const
  {
    return m_gameBoard;
  }

  void PlayScene::setGameBoard(const PlayScene::GameBoard &gb)
  {
    m_gameBoard = gb;
  }

  void PlayScene::addPlayer(const std::shared_ptr<Player> &player)
  {
    for (auto &p : m_listPlayer)
    {
      if (player == p)
      {
        return;
      }
    }
    m_listPlayer.emplace_back(player);
    player->setScene(this);
    player->setCursor(
      Point2D(m_gameBoard.size()/2,
              m_gameBoard.at(m_gameBoard.size()/2).size()/2)
      );
  }

  void PlayScene::removePlayer(const std::shared_ptr<Player> &player)
  {
    for (auto &p : m_listPlayer)
    {
      if (player == p)
      {
        // m_listPlayer.erase(m_listPlayer.begin() + i);
        break;
      }
    }

  }

  PlayScene::ListPlayer PlayScene::getListPlayer() const
  {
    return m_listPlayer;
  }

  void PlayScene::setNextPlayer(const int &nextPlayer)
  {
    if (nextPlayer >= static_cast<int>(m_listPlayer.size()))
    {
      this->m_currentPlayer = 0;
    }
    else
    {
      this->m_currentPlayer = nextPlayer;
    }

    m_listPlayer.at(m_currentPlayer)->setIsTurn(true);
  }

  int PlayScene::getCurrentPlayer() const
  {
    return m_currentPlayer;
  }

} }
