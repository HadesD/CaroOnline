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
    switch (m_getch)
    {
      case 'q':
        {

        }
        break;

    }
  }

}
