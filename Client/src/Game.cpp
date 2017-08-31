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
    }
  }

  void Game::update()
  {

    m_pScene->update();
  }

}
