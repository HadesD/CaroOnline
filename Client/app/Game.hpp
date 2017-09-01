#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <memory>
#include <vector>
#include "app/Point2D.hpp"
#include "app/Scene.hpp"

namespace app {

  class Game : public std::enable_shared_from_this<Game>
  {
    public:
      Game();
      ~Game();

    public:
      void init();
      void run();
      void render();

      /**
       * Update game
       * @return void
       * @param float dt : Delta time
       *
       */
      void update(float dt);
      void waitKeyboardEvent();
      void quit();

    protected:
      bool m_isRunning;
      std::shared_ptr<Scene> m_pScene;

  };

}

#endif
