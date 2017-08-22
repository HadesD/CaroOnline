#include "app/Game.hpp"

#include "../Common/Config.hpp"

namespace app {

  Game::Game()
  {
    m_gameBoard.reserve(GAMEBOARD_ROWS);
    for (int x = 0; x < GAMEBOARD_ROWS; x++)
    {
      m_gameBoard.at(x).reserve(GAMEBOARD_COLS);
      for (int y = 0; y < GAMEBOARD_COLS; y++)
      {
        m_gameBoard.at(x).emplace_back(0);
      }
    }
  }

  Game::~Game()
  {
  }

  void Game::run()
  {
  }

  void Game::init()
  {
  }

}
