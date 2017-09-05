#include "app/Scene.hpp"
#include "app/core/Game.hpp"

namespace app {

  Scene::Scene(std::shared_ptr<app::core::Game> game)
  {
    m_pGame = game;
  }

  Scene::~Scene()
  {
  }

}
