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
  }

  void IntroScene::draw()
  {
  }

  void IntroScene::goToPlay()
  {
  }

} }
