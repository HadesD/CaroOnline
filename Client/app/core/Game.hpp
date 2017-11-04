#ifndef APP_GAME_HPP
#define APP_GAME_HPP
// #define DEBUG
#include <memory>
#include <vector>

namespace app {
  class Scene;
}

namespace app { namespace core {

  class Game : public std::enable_shared_from_this<Game>
  {
    public:
      Game();
      ~Game();

    public:
      void run();
      void quit();
      void setScene(const std::shared_ptr<app::Scene> &scene);

    private:
      void init();
      void render();
      void handleEvent();
      void erase();

      /**
       * Update game
       * @return void
       * @param float dt : Delta time
       */
      void update(const float dt);
      void waitKeyboardEvent();

    protected:
      bool m_isRunning;
      std::shared_ptr<app::Scene> m_pScene;

  };

} }

#endif
