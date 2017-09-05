#include <iostream>

#include "app/scenes/IntroScene.hpp"

#include "app/Game.hpp"

namespace app { namespace scenes {

  IntroScene::IntroScene(std::shared_ptr<app::Game> game) : app::Scene(game)
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

  void IntroScene::update(float /* dt */)
  {
    this->waitKeyboardEvent();
  }

  void IntroScene::draw()
  {
    // std::cout << "sdkfjlsdfj" << std::endl;
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
    }
  }

  void IntroScene::goToPlay()
  {
  }

  void IntroScene::quit()
  {
    m_pGame->quit();
  }

} }
