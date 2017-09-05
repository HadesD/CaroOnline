#ifndef APP_SCENE_HPP
#define APP_SCENE_HPP
#include <memory>

namespace app {

  namespace core
  {
    class Game;
  }

  class Scene
  {
    public:
      Scene(std::shared_ptr<app::core::Game> game);
      ~Scene();

    public:
      virtual void init() = 0;
      virtual void update(float dt) = 0;
      virtual void draw() = 0;
      // virtual void load() = 0;

    protected:
      std::shared_ptr<app::core::Game> m_pGame;

  };

}
#endif
