#ifndef APP_SCENES_INTRO_SCENE_HPP
#define APP_SCENES_INTRO_SCENE_HPP
#include <functional>
#include <map>

#include "app/Game.hpp"
#include "app/Scene.hpp"

#include "app/Kbhit.h"

namespace app { namespace scenes {

  class IntroScene : public app::Scene
  {
    public:
      typedef std::vector< std::map< std::string, void(*)() > > Handle;

    public:
      IntroScene(std::shared_ptr<app::Game> game);
      ~IntroScene();

    public:
      void init();
      void update(float dt);
      void draw();

    public:
      void waitKeyboardEvent();
      void onKeyboardEvent();

    private:
      void goToPlay();
      void quit();

    protected:
      Handle m_selection;
      // std::vector< std::map< std::string, int > > m_selection;
      ::Kbhit m_kbhit;

    private:


  };

} }

#endif
