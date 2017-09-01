#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include <algorithm>
#include <chrono> // update function : float dt
#include <ctime>
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
    m_pScene = std::make_shared<scenes::PlayScene>(this->shared_from_this());
  }

  void Game::render()
  {
    if (m_pScene == nullptr)
    {
      this->quit();
    }
    else
    {
      m_pScene->draw();
    }
  }

  void Game::update(float dt)
  {
    if (m_pScene == nullptr)
    {
      this->quit();
    }
    else
    {
      m_pScene->update(dt);
    }
  }

  void Game::quit()
  {
    m_isRunning = false;
  }

  void Game::run()
  {
    this->init();

    // WindowManager wm;

    std::chrono::time_point<std::chrono::system_clock> now_time =
      std::chrono::system_clock::now();

    while (this->m_isRunning == true)
    {
      system("clear");

      std::chrono::duration<float> dt = std::chrono::system_clock::now() -
        now_time;

      this->update(static_cast<float>(dt.count()));

      this->render();

      now_time = std::chrono::system_clock::now();

      std::cout << dt.count() << std::endl;
    }
  }

}
