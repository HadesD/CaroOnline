#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
// #include <chrono>
// #include <thread>

#include "app/Game.hpp"
#include "app/MoveManager.hpp"

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

  Game::Cursor &Game::Cursor::operator+(const Game::Cursor &c)
  {
    x += c.x;
    y += c.y;
    return *this;
  }

  Game::Cursor &Game::Cursor::operator-(const Game::Cursor &c)
  {
    x -= c.x;
    y -= c.y;
    return *this;
  }

  //------ End Cursor

  Game::Cursor Game::getCursor() const
  {
    return mCursor;
  }

  Game::Game()
  {
    mGameBoard.assign(
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

      this->update();

      if (mKeyPushed == 'q')
      {
        break;
      }

      // std::this_thread::sleep_for(std::chrono::milliseconds(80));

    }
  }

  void Game::update()
  {
    // std::shared_ptr<MoveManager> move(new MoveManager(*(this)));
    MoveManager move(*(this));
    move.waitKeyboardEvent();
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

    for (size_t x = 0; x < mGameBoard.size(); x++)
    {
      drawBarrier(GAMEBOARD_ONEOBJ_SIZE);
      // for (size_t y = 0; y < mGameBoard.at(x).size(); y++)
      // {
      //   drawBody(" ");
      // }
      // std::cout << '|';
      // std::cout << std::endl;
      for (size_t y = 0; y < mGameBoard.at(x).size(); y++)
      {
        std::string curr;
        std::string color;

        Game::Cursor cXY(x, y);
        {
          switch (mGameBoard.at(x).at(y))
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
        if (mCursor == cXY)
        {
          color = "\e[48;5;255m";
        }
        curr += "\e[0m";

        drawLine(color + curr);
      }
      std::cout << '|';
      std::cout << std::endl;
      // for (size_t y = 0; y < mGameBoard.at(x).size(); y++)
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
    mKeyPushed = key;
  }

  void Game::setCursor(const Game::Cursor &c)
  {
    mCursor = c;
  }

  Game::GameBoard Game::getGameBoard() const
  {
    return mGameBoard;
  }

  void Game::setGameBoard(const Game::GameBoard &gb)
  {
    mGameBoard = gb;
  }
}
