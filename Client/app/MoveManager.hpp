#ifndef APP_MOVE_MANAGER_HPP
#define APP_MOVE_MANAGER_HPP

namespace app {

  class Game;

  class MoveManager
  {
    public:
      MoveManager(Game &g);
      ~MoveManager();

    public:
      void waitKeyboardEvent();
      void onKeyboardEvent();

    protected:
      Game &p_game;
      int m_getch;

  };

}

#endif
