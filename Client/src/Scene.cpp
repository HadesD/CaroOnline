#include "app/Scene.hpp"

namespace app {

  Scene::Scene(std::shared_ptr<Game> game)
  {
    m_pGame = game;
  }

  Scene::~Scene()
  {
  }

}
