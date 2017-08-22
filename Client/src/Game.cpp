#include <iostream>
#include <cassert>
#include <cmath>

#include "app/Game.hpp"

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

  bool Game::Cursor::operator==(Game::Cursor &c)
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
      std::vector< int >(GAMEBOARD_COLS, 1)
      );
  }

  Game::~Game()
  {
  }

  void Game::init()
  {
  }

  void Game::run()
  {
    this->init();

    while (true)
    {
      system("clear");

      this->drawGameBoard();

      std::string k;
      std::cin >> k;
      if (k == "q")
      {
        break;
      }
    }
  }

  // #undef GAMEBOARD_ONEOBJ_SIZE
  // #define GAMEBOARD_ONEOBJ_SIZE 5

  void Game::drawGameBoard()
  {
    assert((GAMEBOARD_ONEOBJ_SIZE % 2) != 0);
    // Barrier
    auto drawBarrier = [](int len){
      for (size_t i = 0; i < GAMEBOARD_COLS; i++)
      {
        std::cout << '+';
        std::cout << std::string(len, '-');
      }
      std::cout << '+';
      std::cout << std::endl;
    };

    // Body
    auto drawLine = [](const std::string s){
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

        Game::Cursor cXY(x, y);
        {
          switch (m_gameBoard.at(x).at(y))
          {
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
        }
        if (m_cursor == cXY)
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
}
