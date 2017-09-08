#include <iostream>

#include "app/scenes/IntroScene.hpp"

#include "../Common/Network.hpp"
#include "app/core/Game.hpp"
#include "app/scenes/PlayScene.hpp"

namespace app { namespace scenes {

  IntroScene::IntroScene(const std::shared_ptr<app::core::Game> &game) : app::Scene(game)
  {
  }

  IntroScene::~IntroScene()
  {
  }

  void IntroScene::init()
  {
    // m_selection.push_back({"", [](){}});
    // m_selection.push_back({"", ""});
  }

  void IntroScene::update(const float &/* dt */)
  {
    this->waitKeyboardEvent();
  }

  void IntroScene::draw()
  {
    // std::cout << "sdkfjlsdfj" << std::endl;
    for (std::size_t i = 0; i < m_selection.size(); i++)
    {
      std::cout << i << std::endl;
    }
  }

  void IntroScene::waitKeyboardEvent()
  {
    if (m_kbhit.kbhit())
    {
      this->onKeyboardEvent();
    }
  }

  void IntroScene::onKeyboardEvent()
  {
    switch(m_kbhit.getch())
    {
      case 'q':
        {
          this->quit();
        }
        break;
      case 'p':
        {
          this->goToPlay();
        }
        break;
    }
  }

  void IntroScene::goToPlay()
  {
    m_pGame->setScene(std::shared_ptr<app::scenes::PlayScene>(new
                                                              app::scenes::PlayScene(m_pGame)));
  }

  void IntroScene::quit()
  {
    m_pGame->quit();
  }

} }
