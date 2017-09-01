#ifndef APP_SCENE_HPP
#define APP_SCENE_HPP
#include <memory>

namespace app {

  class Game;

  class Scene : public std::enable_shared_from_this<Scene>
  {
    public:
      Scene(std::shared_ptr<Game> game);
      ~Scene();

    public:
      virtual void update(float dt) = 0;
      virtual void draw() = 0;
      // virtual void load() = 0;

    protected:
      std::shared_ptr<Game> m_pGame;

  };

}
#endif
