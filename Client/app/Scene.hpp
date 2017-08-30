#ifndef APP_SCENE_HPP
#define APP_SCENE_HPP

namespace app {

  class Scene
  {
    public:
      Scene();
      ~Scene();

    public:
      virtual void update() = 0;
      virtual void redraw() = 0;
      // virtual void load() = 0;

  };

}
#endif
