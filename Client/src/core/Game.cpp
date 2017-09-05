#include <iostream>
#include <cassert>
#include <memory>
#include <cmath>
#include <algorithm>
#include <chrono> // update function : float dt
#include <ctime>
#include <thread>
// #include <chrono>
// #include <thread>

#include "../Common/Config.hpp"

#include "app/core/Game.hpp"
#include "app/WindowManager.h"
#include "app/Config.hpp"

#include "app/Scene.hpp"
// #include "app/scenes/PlayScene.hpp"
#include "app/scenes/IntroScene.hpp"

namespace app { namespace core {

  Game::Game()
  {
    m_isRunning = true;
  }

  Game::~Game()
  {
  }

  void Game::init()
  {
    // m_pScene = std::make_shared<scenes::PlayScene>(this->shared_from_this());
    m_pScene = std::make_shared<scenes::IntroScene>(this->shared_from_this());

    m_pScene->init();
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

    int fixed_fps = 15;

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

      long wait = 1000 / fixed_fps - dt.count() * 1000;

      std::cout << "FPS: " << (1000 / (wait == 0 ? (1000/fixed_fps) : wait)) << std::endl;

      if (wait > 0)
      {
        std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(wait));
      }
    }
  }

} }
