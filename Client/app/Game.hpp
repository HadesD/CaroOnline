#ifndef APP_GAME_HPP
#define APP_GAME_HPP
#include <vector>

namespace app {

  class Game
  {
    public:
      typedef std::vector< std::vector< int > > GameBoard;

    public:
      Game();
      ~Game();

    public:
      void run();
      void init();

    protected:
      GameBoard m_gameBoard;

  };

}

#endif
