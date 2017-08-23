#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
// #include <chrono>
// #include <thread>

#include "app/Game.hpp"
#include "app/Player.hpp"
#include "app/Kbhit.h"

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
  }

  Game::~Game()
  {
  }

  void Game::init()
  {
    // try
    {
      std::shared_ptr<Player> p(new Player());
      this->addPlayer(p);
      std::cout << p << std::endl;
      std::string k; std::cin >> k;
    }
    // catch (std::bad_weak_ptr &e)
    {
      // std::cout << e.what() << std::endl;
    }
  }

  void Game::run()
  {
    this->init();

    while (true)
    {
      system("clear");

      this->drawGameBoard();

      std::cout << "Players: " << m_listPlayer.size() << std::endl;

      this->update();

      if (m_keyPushed == 'q')
      {
        break;
      }

      // std::this_thread::sleep_for(std::chrono::milliseconds(80));

    }
  }

  void Game::update()
  {
    // std::shared_ptr<MoveManager> move(new MoveManager(*(this)));
    this->waitKeyboardEvent();

    for (auto &p : m_listPlayer)
    {
      p->onKeyboardEvent();
    }
  }

  void Game::waitKeyboardEvent()
  {
    m_keyPushed = (new ::Kbhit())->getch();
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

  void Game::addPlayer(std::shared_ptr<Player> player)
  {
    m_listPlayer.emplace_back(player);
    player->setGame(this->shared_from_this());
  }
}
