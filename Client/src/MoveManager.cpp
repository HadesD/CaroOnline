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

    int toX = gc.x;
    int toY = gc.y;

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
          if (gc.x > 0)
          {
            toX -= 1;
          }
        }
        break;
      case 'j':
      case 's':
        {
          if (gc.x < (static_cast<int>(gb.size()) - 1))
          {
            toX += 1;
          }
        }
        break;
      case 'h':
      case 'a':
        {
          if (gc.y > 0)
          {
            toY -= 1;
          }
        }
        break;
      case 'd':
      case 'l':
        {
          if (gc.y < (static_cast<int>(gb.at(gc.x).size()) - 1))
          {
            toY += 1;
          }
        }
        break;
    }
    if (!(gc == Game::Cursor(toX, toY)))
    {
      p_game.setCursor(Game::Cursor(toX, toY));
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
