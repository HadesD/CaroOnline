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

    public:
      void moveUp();
      void moveDown();
      void moveLeft();
      void moveRight();

    protected:
      Game &p_game;
      int m_getch;

  };

}

#endif
