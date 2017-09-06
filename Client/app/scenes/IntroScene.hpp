#ifndef APP_SCENES_INTRO_SCENE_HPP
#define APP_SCENES_INTRO_SCENE_HPP
#include <functional>
#include <vector>
#include <map>

#include "app/Scene.hpp"

#include "app/input/Kbhit.hpp"

namespace app
{
  namespace core
  {
    class Game;
  }
}

namespace app { namespace scenes {

  class IntroScene : public app::Scene
  {
    public:
      typedef std::vector< std::map< std::string, void(*)() > > Handle;

    public:
      IntroScene(const std::shared_ptr<app::core::Game> &game);
      ~IntroScene();

    public:
      void init();
      void update(const float &dt);
      void draw();

    public:
      void waitKeyboardEvent();
      void onKeyboardEvent();

    private:
      void goToPlay();
      void quit();

    protected:
      Handle m_selection;
      app::input::Kbhit m_kbhit;

  };

} }

#endif
