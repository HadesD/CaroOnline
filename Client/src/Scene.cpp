#include "app/Scene.hpp"
#include "app/core/Game.hpp"

namespace app {

  Scene::Scene(const std::shared_ptr<app::core::Game> &game)
  {
    m_pGame = game;
  }

  Scene::~Scene()
  {
  }

}
