#ifndef APP_SCENES_INTRO_SCENE_HPP
#define APP_SCENES_INTRO_SCENE_HPP
#include <functional>
#include <map>

#include "app/Game.hpp"
#include "app/Scene.hpp"


namespace app { namespace scenes {

  class IntroScene : public app::Scene
  {
    public:
      IntroScene(std::shared_ptr<app::Game> game);
      ~IntroScene();

    public:
      void init();
      void update(float dt);
      void draw();

    private:
      void goToPlay();

    protected:
      std::vector< std::map< std::string, void(*)() > > m_selection;
      // std::vector< std::map< std::string, int > > m_selection;

  };

} }

#endif
