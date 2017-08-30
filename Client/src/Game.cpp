#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include <algorithm>
// #include <chrono>
// #include <thread>

#include "../Common/Config.hpp"

#include "app/Game.hpp"
#include "app/Player.hpp"
#include "app/Kbhit.h"
#include "app/WindowManager.h"
#include "app/Config.hpp"

namespace app {

  //------ Cursor

  Game::Cursor::Cursor() : Point2D()
  {
  }

  Game::Cursor::Cursor(int x, int y) : Point2D(x, y)
  {
  }

  Game::Cursor::~Cursor()
  {
  }

  //------ End Cursor

  Game::Game()
  {
    m_gameBoard.assign(
      common::config::gameBoardRows,
      std::vector< int >(common::config::gameBoardCols, 0)
      );

    isFinish = false;
  }

  Game::~Game()
  {
  }

  void Game::init()
  {
    std::shared_ptr<Player> p1(new Player());
    p1->setId(1);
    p1->setMark(1);
    p1->setIsTurn(true);
    this->addPlayer(p1);
    m_currentPlayer = 0;

    std::shared_ptr<Player> p2(new Player());
    this->addPlayer(p2);
    p2->setId(222);
    p2->setMark(2);

    std::shared_ptr<Player> p3(new Player());
    // this->addPlayer(p3);
    p3->setId(32);
    p3->setMark(3);

    // std::cout << p << std::endl;
    // std::string k; std::cin >> k;

    // Set default cursor
    this->m_cursor = m_listPlayer.front()->getCursor();
  }

  void Game::run()
  {
    this->init();

    WindowManager wm;

    while (this->isFinish == false)
    {
      system("clear");

      this->drawGameBoard();

      std::cout << "Players: " << m_listPlayer.size() << std::endl;
      std::cout << "Turn of: " << m_currentPlayer << std::endl;

      int xP, yP, x0, y0, xMaxSize, yMaxSize;

      std::weak_ptr<Player> playerToCheck = m_listPlayer.at(m_currentPlayer);

      xP = playerToCheck.lock()->getCursor().x;
      yP = playerToCheck.lock()->getCursor().y;

      x0 = std::max(xP - common::config::maxCoupleCount, 0);
      y0 = std::max(yP - common::config::maxCoupleCount, 0);

      xMaxSize = std::min(xP + common::config::maxCoupleCount + 1,
                          static_cast<int>(m_gameBoard.size()));
      yMaxSize = std::min(yP + common::config::maxCoupleCount + 1,
                          static_cast<int>(m_gameBoard.at(xMaxSize-1).size()));

      std::cout << "x0: " << x0 << " ,y0: " << y0 << ". xMaxSize:" << xMaxSize << " , yMaxSize: " << yMaxSize << std::endl;
      std::cout << "xPlayer: " << xP << ", yPlayer: " << yP << std::endl;

      this->update();

      if (m_keyPushed == 'q')
      {
        break;
      }

      m_keyPushed = 0;
    }
  }

  void Game::update()
  {
    this->waitKeyboardEvent();

    this->m_cursor = m_listPlayer.at(m_currentPlayer)->getCursor();
  }

  void Game::waitKeyboardEvent()
  {
    m_keyPushed = (new ::Kbhit())->getch();

    std::weak_ptr<Player> p = m_listPlayer.at(m_currentPlayer);

    p.lock()->onKeyboardEvent();
  }

  void Game::checkFinish()
  {
    int xP, yP, x0, y0, xMaxSize, yMaxSize;

    std::weak_ptr<Player> playerToCheck = m_listPlayer.at(m_currentPlayer);

    xP = playerToCheck.lock()->getCursor().x;
    yP = playerToCheck.lock()->getCursor().y;

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
        (m_gameBoard.at(xP).at(y) == playerToCheck.lock()->getMark()) &&
        (m_gameBoard.at(xP).at(y + 1) == playerToCheck.lock()->getMark())
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
        this->isFinish = true;
        return;
      }
    }

    // Check vert
    count = 0;
    for (int x = x0; x < xMaxSize - 1; x++)
    {
      if (
        (m_gameBoard.at(x).at(yP) == playerToCheck.lock()->getMark()) &&
        (m_gameBoard.at(x + 1).at(yP) == playerToCheck.lock()->getMark())
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
        this->isFinish = true;
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
        (m_gameBoard.at(x).at(y) == playerToCheck.lock()->getMark()) &&
        (m_gameBoard.at(x + 1).at(y + 1) == playerToCheck.lock()->getMark())
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
        this->isFinish = true;
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
        (m_gameBoard.at(x).at(y) == playerToCheck.lock()->getMark()) &&
        (m_gameBoard.at(x + 1).at(y - 1) == playerToCheck.lock()->getMark())
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
        this->isFinish = true;
        return;
      }
    }
  }

  // #undef app::config::gameBoardOneObjSize
  // #define app::config::gameBoardOneObjSize 5

  void Game::drawGameBoard()
  {
    assert((app::config::gameBoardOneObjSize % 2) != 0);
    // Barrier
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
    auto drawLine = [](const std::string &s){
      std::cout << '|';
      std::cout << std::string(app::config::gameBoardOneObjSize / 2, ' ');
      std::cout << s;
      std::cout << std::string(app::config::gameBoardOneObjSize / 2, ' ');
    };

    for (size_t x = 0; x < m_gameBoard.size(); x++)
    {
      drawBarrier(app::config::gameBoardOneObjSize);
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
        if (m_cursor == Game::Cursor(x, y))
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
    drawBarrier(app::config::gameBoardOneObjSize);
  }

  void Game::setKeyPushed(const int &key)
  {
    m_keyPushed = key;
  }

  int Game::getKeyPushed() const
  {
    return m_keyPushed;
  }

  Game::Cursor Game::getCursor() const
  {
    return m_cursor;
  }

  void Game::setCursor(const Game::Cursor &c)
  {
    m_cursor = c;
  }

  Game::GameBoard Game::getGameBoard() const
  {
    return m_gameBoard;
  }

  void Game::setGameBoard(const Game::GameBoard &gb)
  {
    m_gameBoard = gb;
  }

  void Game::addPlayer(const std::shared_ptr<Player> &player)
  {
    for (auto &p : m_listPlayer)
    {
      if (player == p)
      {
        return;
      }
    }
    m_listPlayer.emplace_back(player);
    player->setGame(this->shared_from_this());
    player->setCursor(
      Cursor(m_gameBoard.size()/2,
             m_gameBoard.at(m_gameBoard.size()/2).size()/2)
      );
  }

  void Game::removePlayer(const std::shared_ptr<Player> &player)
  {
    for (std::size_t i = 0; i < m_listPlayer.size(); i++)
    {
      if (player == m_listPlayer.at(i))
      {
        // m_listPlayer.erase(m_listPlayer.begin() + i);
        break;
      }
    }
  }

  Game::ListPlayer Game::getListPlayer() const
  {
    return m_listPlayer;
  }

  void Game::setNextPlayer(const int &nextPlayer)
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

  int Game::getCurrentPlayer() const
  {
    return m_currentPlayer;
  }
}
