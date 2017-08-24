#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
// #include <chrono>
// #include <thread>

#include "app/Game.hpp"
#include "app/Player.hpp"
#include "app/Kbhit.h"
#include "app/WindowManager.h"

#include "../Common/Config.hpp"

namespace app {

  //------ Cursor

  Game::Cursor::Cursor()
  {
  }

  Game::Cursor::~Cursor()
  {
  }

  Game::Cursor::Cursor(int x, int y) : x(x), y(y)
  {
  }

  bool Game::Cursor::operator==(const Game::Cursor &c)
  {
    return (x == c.x) && (y == c.y);
  }

  //------ End Cursor

  Game::Cursor Game::getCursor() const
  {
    return m_cursor;
  }

  Game::Game()
  {
    m_gameBoard.assign(
      GAMEBOARD_ROWS,
      std::vector< int >(GAMEBOARD_COLS, 0)
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

    std::shared_ptr<Player> p2(new Player());
    this->addPlayer(p2);
    p2->setId(222);
    p2->setMark(2);

    std::shared_ptr<Player> p3(new Player());
    this->addPlayer(p3);
    p3->setId(32);
    p3->setMark(3);

    // std::cout << p << std::endl;
    // std::string k; std::cin >> k;
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

      this->update();

      if (m_keyPushed == 'q')
      {
        break;
      }

      m_keyPushed = 0;

      // std::this_thread::sleep_for(std::chrono::milliseconds(80));

    }
  }

  void Game::update()
  {
    this->checkFinish();

    this->waitKeyboardEvent();
  }

  void Game::waitKeyboardEvent()
  {
    m_keyPushed = (new ::Kbhit())->getch();

    int i = 0;
    for (auto &p : m_listPlayer)
    {
      i++;
      if (p->getIsTurn() == true)
      {
        p->onKeyboardEvent();
        if (!(this->m_cursor == p->getCursor()))
        {
          this->m_cursor = p->getCursor();
        }
        std::cout << "Turn: " << i << std::endl;
      }
    }
  }

  void Game::checkFinish()
  {
    // this->isFinish = true;
  }

  // #undef GAMEBOARD_ONEOBJ_SIZE
  // #define GAMEBOARD_ONEOBJ_SIZE 5

  void Game::drawGameBoard()
  {
    assert((GAMEBOARD_ONEOBJ_SIZE % 2) != 0);
    // Barrier
    auto drawBarrier = [](const int &len){
      for (size_t i = 0; i < GAMEBOARD_COLS; i++)
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
      std::cout << std::string(GAMEBOARD_ONEOBJ_SIZE / 2, ' ');
      std::cout << s;
      std::cout << std::string(GAMEBOARD_ONEOBJ_SIZE / 2, ' ');
    };

    for (size_t x = 0; x < m_gameBoard.size(); x++)
    {
      drawBarrier(GAMEBOARD_ONEOBJ_SIZE);
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
              color = "\e[38;5;22m";
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
    drawBarrier(GAMEBOARD_ONEOBJ_SIZE);
  }

  void Game::setKeyPushed(const int &key)
  {
    m_keyPushed = key;
  }

  int Game::getKeyPushed() const
  {
    return m_keyPushed;
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
}
