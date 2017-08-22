#ifndef APP_MOVE_MANAGER_HPP
#define APP_MOVE_MANAGER_HPP
#include "Kbhit.h"

namespace app {

  class Game;

  class MoveManager
  {
    public:
      MoveManager(Game g);
      ~MoveManager();

    protected:
      Game &p_game;

  };

}

#endif
