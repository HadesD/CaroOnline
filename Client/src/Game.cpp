#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include <algorithm>
// #include <chrono>
// #include <thread>

#include "../Common/Config.hpp"

#include "app/Game.hpp"
#include "app/Player.hpp"
#include "app/Kbhit.h"
#include "app/WindowManager.h"
#include "app/Config.hpp"

#include "app/scenes/PlayScene.hpp"

namespace app {

  Game::Game()
  {
    m_isRunning = true;
  }

  Game::~Game()
  {
  }

  void Game::init()
  {
  }

  void Game::render()
  {
    m_pScene->draw();
  }

  void Game::run()
  {
    this->init();

    WindowManager wm;

    while (this->m_isRunning == false)
    {
      system("clear");

      this->render();

      this->update();

      if (m_keyPushed == 'q')
      {
        break;
      }

      m_keyPushed = 0;
    }
  }

  void Game::update()
  {
    this->waitKeyboardEvent();

    m_pScene->update();
  }

  void Game::waitKeyboardEvent()
  {
    m_keyPushed = (new ::Kbhit())->getch();
  }

  // #undef app::config::gameBoardOneObjSize
  // #define app::config::gameBoardOneObjSize 5

  void Game::setKeyPushed(const int &key)
  {
    m_keyPushed = key;
  }

  int Game::getKeyPushed() const
  {
    return m_keyPushed;
  }

}
