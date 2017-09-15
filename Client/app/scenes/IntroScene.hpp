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
      struct Selection
      {
        Selection(const std::string &n, const std::function<void()> &c) :
          name(n)
          , call(c)
        {}
        std::string name;
        std::function<void()> call;
      };

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
      std::vector<Selection> m_selection;
      std::size_t m_cursor;
      app::input::Kbhit m_kbhit;

  };

} }

#endif
