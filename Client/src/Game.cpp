#include <iostream>

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
    for (size_t x = 0; x < m_gameBoard.size(); x++)
    {
      for (size_t y = 0; y < m_gameBoard.at(x).size(); y++)
      {
        std::cout << m_gameBoard.at(x).at(y);
      }
      std::cout << std::endl;
    }
  }
}
