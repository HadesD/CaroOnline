#include <iostream>
#include <cassert>
#include <cmath>

#include "app/Game.hpp"

#include "../Common/Config.hpp"

namespace app {

  Game::Game()
  {
    m_gameBoard.assign(GAMEBOARD_ROWS, std::vector< int >(GAMEBOARD_COLS, 0));
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

  void Game::drawGameBoard()
  {
    // Header
    auto drawBarrier = [=](int len){
      for (size_t i = 0; i < GAMEBOARD_COLS; i++)
      {
        std::cout << '+';
        std::cout << std::string(len, '-');
      }
      std::cout << '+';
      std::cout << std::endl;
    };

    assert((GAMEBOARD_ONEOBJ_SIZE % 2) != 0);

    for (size_t x = 0; x < m_gameBoard.size(); x++)
    {
      drawBarrier(GAMEBOARD_ONEOBJ_SIZE);
      for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      {
        std::cout << '|';
        std::cout << std::string(GAMEBOARD_ONEOBJ_SIZE / 2, ' ');
        std::cout << m_gameBoard.at(x).at(y);
        std::cout << std::string(GAMEBOARD_ONEOBJ_SIZE / 2, ' ');
      }
      std::cout << '|';
      std::cout << std::endl;
    }
    drawBarrier(GAMEBOARD_ONEOBJ_SIZE);
  }
}
