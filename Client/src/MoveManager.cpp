#include "app/MoveManager.hpp"
#include "app/Game.hpp"
#include "app/Kbhit.h"

#include <iostream>

namespace app {

  MoveManager::MoveManager(Game &g) : p_game(g)
  {
  }

  MoveManager::~MoveManager()
  {}

  void MoveManager::waitKeyboardEvent()
  {
    m_getch = (new ::Kbhit())->getch();
    this->onKeyboardEvent();
  }

  void MoveManager::onKeyboardEvent()
  {
    p_game.setKeyPushed(m_getch);
    std::cout << m_getch << std::endl;
    Game::GameBoard gb = p_game.getGameBoard();
    Game::Cursor gc = p_game.getCursor();

    switch (m_getch)
    {
      case 'q':
        {
          return;
        }
        break;
      case 10:
      case 32:
        {
        }
        break;
      case 'k':
      case 'w':
        {
          p_game.setCursor(gc - Game::Cursor(1, 0));
        }
        break;
      case 'j':
      case 's':
        {
          p_game.setCursor(gc + Game::Cursor(1, 0));
        }
        break;
      case 'h':
      case 'a':
        {
          p_game.setCursor(gc - Game::Cursor(0, 1));
        }
        break;
      case 'd':
      case 'l':
        {
          p_game.setCursor(gc + Game::Cursor(0, 1));
        }
        break;
    }
    p_game.setGameBoard(gb);
  }

  void MoveManager::moveUp()
  {

  }

  void MoveManager::moveDown()
  {

  }

  void MoveManager::moveLeft()
  {

  }

  void MoveManager::moveRight()
  {

  }

}
