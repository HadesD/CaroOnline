#ifndef APP_SCENE_HPP
#define APP_SCENE_HPP
#include <memory>

namespace app {

  class Scene : public std::enable_shared_from_this<Scene>
  {
    public:
      // Scene();
      // ~Scene();

    public:
      virtual void update() = 0;
      virtual void draw() = 0;
      // virtual void load() = 0;

  };

}
#endif
